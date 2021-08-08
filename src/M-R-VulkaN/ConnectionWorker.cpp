#include "ConnectionWorker.h"
#include <iostream>
#include <chrono>
#include <shared_timed_mutex>

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;
ConnectionWorker::ConnectionWorker(Connection &con) : _conAtomicPtr(&con)
{
    _receivingThread = std::thread(&ConnectionWorker::receivePacketsThreadFunc, this);
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
    std::lock_guard<std::mutex> lock(_threadSleepMutex);
    _deactivateThread = false;

    _threadSleepConVar.notify_all();
}
void ConnectionWorker::stop()
{
    std::lock_guard<std::mutex> lock(_threadSleepMutex);
    _deactivateThread = true;

    _threadSleepConVar.notify_all();
}
void ConnectionWorker::addCallback(const PacketCallbackBundle &callback)
{
    std::lock_guard<std::mutex> lock(_callbackMutex);
    _paramReceivedCallbacks.push_back(callback);
}

void ConnectionWorker::receivePacketsThreadFunc()
{
    Packet p_recv;
    while (true)
    {
 
        if (_deactivateThread)
        {
            std::atomic<bool>* deactivateThreadPtr = &_deactivateThread;
            std::unique_lock<std::mutex> lock(_threadSleepMutex);
            _threadSleepConVar.wait(lock, [deactivateThreadPtr](){return !*deactivateThreadPtr;});
        }


        if (_conAtomicPtr)
        {
            p_recv = ((Connection *)_conAtomicPtr)->recv(1);
        }
        else
            break;

        if (p_recv && !_deactivateThread)
        {
            std::lock_guard<std::mutex> lock(_callbackMutex);

            // if(p_recv.port() == 5 && p_recv.channel()==2)
                std::cout << p_recv <<std::endl;
            auto* paramReceivedCallbacksPtr = &_paramReceivedCallbacks;
            auto* p_recvPtr=&p_recv;
            std::unique_lock<std::shared_timed_mutex> uniqueLock(_callbackSharedMutex,std::defer_lock);
            std::shared_lock<std::shared_timed_mutex> sharedLock(_callbackSharedMutex,std::defer_lock);
            auto* callbackSharedMutexPtr = &_callbackSharedMutex;
            sharedLock.lock();
            for(auto it = _paramReceivedCallbacks.begin(); it != _paramReceivedCallbacks.end(); it++)
            {
                auto* itPtr = &it;
                if(p_recv.channel() == it->_channel && it->_port == p_recv.port())
                {
                    std::thread thread([paramReceivedCallbacksPtr, itPtr,p_recvPtr, callbackSharedMutexPtr](){
                        if(!(*itPtr)->_packetCallbackFunc(*p_recvPtr))
                        {
                            std::unique_lock<std::shared_timed_mutex> lock(*callbackSharedMutexPtr);
                            paramReceivedCallbacksPtr->erase(*itPtr);
                        }
                    });
                    thread.detach();
                }
            }
            sharedLock.unlock();

            // while (it != _paramReceivedCallbacks.end())
            // {
            //     if (p_recv.channel() == it->_channel && it->_port == p_recv.port() && !it->_packetCallbackFunc(p_recv))
            //     {
            //         it = _paramReceivedCallbacks.erase(it);
            //         continue;
            //     }
            //     else
            //     {
            //         it++;
            //     }
            // }
          
        }
    }
}
void ConnectionWorker::send(const Packet &p)
{
    ((Connection *)_conAtomicPtr)->send(p);
}
