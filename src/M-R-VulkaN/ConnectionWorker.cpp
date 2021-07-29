#include "ConnectionWorker.h"
#include <iostream>
#include <chrono>

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;
ConnectionWorker::ConnectionWorker(Connection &con) : _conAtomicPtr(&con)
{
    // ((Connection*)_conAtomicPtr) = &con;
    _receivingThread = std::thread(&ConnectionWorker::receivePacketsThreadFunc, this);
    _isThreadSleeping = true;
    _deactivateThread = true;
    _receivingThread.detach();
}
ConnectionWorker::~ConnectionWorker()
{
    _conAtomicPtr = nullptr;
    this->stop();
}
void ConnectionWorker::start()
{

    std::unique_lock<std::mutex> lock(_threadSleepMutex);
    _deactivateThread = false;

    const std::atomic<bool> *isSleepingPtr = &_isThreadSleeping;

    _threadSleepConVar.wait(lock, [isSleepingPtr]()
                            { return !(*isSleepingPtr); });
}
void ConnectionWorker::stop()
{
    std::unique_lock<std::mutex> lock(_threadSleepMutex);
    _deactivateThread = true;
    const std::atomic<bool> *isSleepingPtr = &_isThreadSleeping;
    // const std::atomic<bool> * isSleepingPtr = &_isThreadSleeping;

    _threadSleepConVar.wait(lock, [isSleepingPtr]()
                            { return (bool)*isSleepingPtr; });
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
        // std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        while (_deactivateThread)
        {

            if (!_isThreadSleeping)
            {
                _isThreadSleeping = true;
                _threadSleepConVar.notify_all();
            }
            if (nullptr == _conAtomicPtr)
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        if (_isThreadSleeping)
        {
            _isThreadSleeping = false;
            _threadSleepConVar.notify_all();
        }

        // _conAtomicPtr->recv
        if (_conAtomicPtr)
        {
            p_recv = ((Connection*)_conAtomicPtr)->recv(1);
        }
        else
            break;
        // {
        //     std::lock_guard<std::mutex> lock(_post)
        // }
        if (p_recv && !_deactivateThread)
        {
            auto it = _paramReceivedCallbacks.begin();
            while ( it != _paramReceivedCallbacks.end())
            {
                if (p_recv.channel() == it->_channel && it->_port == p_recv.port() && !it->_packetCallbackFunc(p_recv))
                {
                    it =_paramReceivedCallbacks.erase(it);
                    continue;
                }
                else
                {
                    it++;
                }
            }
            _receivedPackets.push_back(p_recv);
        }
    }
}
void ConnectionWorker::send(const Packet& p)
{
    // std::lock_guard<std::mutex> lock(_conMutex);
    ((Connection*)_conAtomicPtr)->send(p);
}


