#include "ConnectionWorker.h"
#include <iostream>
#include <chrono>

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;
ConnectionWorker::ConnectionWorker(Connection &con)
{
    _conPtr = &con;
    _receivingThread = std::thread(&ConnectionWorker::receivePacketsThreadFunc, this);
    _isThreadSleeping = true;
    _deactivateThread = true;
    _receivingThread.detach();
}
ConnectionWorker::~ConnectionWorker()
{
    _conPtr = nullptr;
    this->stop();
}
void ConnectionWorker::start()
{

    std::unique_lock<std::mutex> lock(_threadSleepMutex);
    _deactivateThread = false;

    const std::atomic<bool> * isSleepingPtr = &_isThreadSleeping;

    _threadSleepConVar.wait(lock, [isSleepingPtr]()
                            { return !(*isSleepingPtr); });
}
void ConnectionWorker::stop()
{
    std::unique_lock<std::mutex> lock(_threadSleepMutex);
    _deactivateThread = true;
    const std::atomic<bool> * isSleepingPtr = &_isThreadSleeping;
    // const std::atomic<bool> * isSleepingPtr = &_isThreadSleeping;

    _threadSleepConVar.wait(lock, [isSleepingPtr]()
                            { return (bool)*isSleepingPtr;});

}
void ConnectionWorker::addCallback(const PacketCallbackBundle &callback)
{
    _paramReceivedCallbacks.push_back(callback);
}

void ConnectionWorker::receivePacketsThreadFunc()
{
    Packet p_recv;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (_deactivateThread)
        {

            if(!_isThreadSleeping)
        {
        _isThreadSleeping = true;
        _threadSleepConVar.notify_all();
        }
            if (nullptr == _conPtr)
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        if(_isThreadSleeping)
        {
        _isThreadSleeping = false;
        _threadSleepConVar.notify_all();
        }
        
        // _conPtr->recv
        if (_conPtr)
            p_recv = _conPtr->recv(1);
        else
            break;

        if (p_recv && !_deactivateThread)
        {

            std::lock_guard<std::mutex> lock(_packetRecvMutex);
            for (auto it = _paramReceivedCallbacks.begin(); it != _paramReceivedCallbacks.end(); it++)
            {
                if (p_recv.channel() == it->_channel && it->_port == p_recv.port())
                {
                    if (!it->_packetCallbackFunc(p_recv))
                    {
                        _paramReceivedCallbacks.erase(it);
                    }
                }
            }
            _receivedPackets.push_back(p_recv);
        }
    }
}