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
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (_deactivateThread)
        {

            if (!_isThreadSleeping)
            {
                _isThreadSleeping = true;
                _threadSleepConVar.notify_all();
            }
            if (nullptr == _conPtr)
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        if (_isThreadSleeping)
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
    _conPtr->send(p);
}


Packet ConnectionWorker::recv(uint8_t port, uint8_t channel, unsigned long timeout)
{
    std::mutex mu;
    std::unique_lock<std::mutex> lock(mu);
    std::condition_variable waitForRecv;
    std::condition_variable *waitForRecvPtr = &waitForRecv;
    std::atomic<bool> isResultReturned( false);
    std::atomic<bool>* isResultReturnedPtr = &isResultReturned;
    // std::cout << "test" << std::endl;
    Packet res;
    Packet *resPtr = &res;
    this->addCallback({port,channel,(std::function<bool(bitcraze::crazyflieLinkCpp::Packet)>)[resPtr,waitForRecvPtr, isResultReturnedPtr](Packet p_recv){ 
        *resPtr = p_recv;
         waitForRecvPtr->notify_all();
         *isResultReturnedPtr = true;
         return false;}});
    if(0 == timeout)
    {
        waitForRecv.wait(lock ,[isResultReturnedPtr](){return (bool)*isResultReturnedPtr;});
    }
    else
    {
        waitForRecv.wait_for(lock,std::chrono::milliseconds(timeout) ,[isResultReturnedPtr](){return (bool)*isResultReturnedPtr;});
    }
    // std::cout << "test2 "<< res << std::endl;

    return res;
}
