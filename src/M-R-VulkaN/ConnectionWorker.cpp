#include "ConnectionWorker.h"
#include <iostream>
#include <chrono>
// #include <atomic>

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;
ConnectionWorker::ConnectionWorker(Connection &con) : _waitForNewPacketPermiable(_sendPackets, _threadsActiveFlag)
{
    _conPtr = &con;
    _sendingThread = std::thread(&ConnectionWorker::sendPacketsThreadFunc, this);
    _receivingThread = std::thread(&ConnectionWorker::receivePacketsThreadFunc, this);

    _threadsActiveFlag = false;
    _sendingThread.detach();
    _receivingThread.detach();
}
ConnectionWorker::~ConnectionWorker()
{
    _conPtr = nullptr;
    this->stop();
}
void ConnectionWorker::start()
{
    _threadsActiveFlag = true;
}
void ConnectionWorker::stop()
{
    _threadsActiveFlag = false;
    _packetSendConditionVariable.notify_all();
}
void ConnectionWorker::sendPacket(const Packet &packetToSend)
{
    std::lock_guard<std::mutex> lock(_packetSendMutex);
    _sendPackets.push(packetToSend);
}

Packet ConnectionWorker::recvPacket(uint8_t port, uint8_t channel)
{
    Packet res;
    for (auto it = _receivedPackets.begin(); it != _receivedPackets.end(); it++)
    {
        if (it->channel() == channel && it->port() == port)
        {
            std::lock_guard<std::mutex> lock(_packetRecvMutex);
            res = *it;
            _receivedPackets.erase(it);
            break;
        }
    }
    return res;
}

void ConnectionWorker::debugPrint(const std::string& msg) 
{
    std::lock_guard<std::mutex> lock(_debugPrintMutex);

    std::cout<< msg << std::endl;
}

bool ConnectionWorker::sendPacketsWait()
{
    return !_sendPackets.empty() || !_threadsActiveFlag; 
}


void ConnectionWorker::sendPacketsThreadFunc()
{
    std::unique_lock<std::mutex> packetsToSendLock(_packetSendMutex, std::defer_lock);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        while (!_threadsActiveFlag)
        {
            if(nullptr == _conPtr )
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        this->debugPrint("pass send");
        packetsToSendLock.lock();
        this->debugPrint("pass send1");

        _packetSendConditionVariable.wait(packetsToSendLock,_waitForNewPacketPermiable);
                                           
        if(!_threadsActiveFlag)
            continue;
        this->debugPrint("pass send2");

        Packet pToSend =  _sendPackets.front();
        _sendPackets.pop() ;
        packetsToSendLock.unlock();

        {
            std::lock_guard<std::mutex> lock(_conMutex);
            _conPtr->send(pToSend);
        }
    }
}
void ConnectionWorker::receivePacketsThreadFunc()
{
    Packet p_recv;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        while (!_threadsActiveFlag)
        {
             if(nullptr == _conPtr )
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        this->debugPrint("pass recv");

        {
            std::lock_guard<std::mutex> lock(_conMutex);
            p_recv = _conPtr->recv(2);
        }
        if (p_recv && _threadsActiveFlag)
        {
            std::lock_guard<std::mutex> lock(_packetRecvMutex);
            _receivedPackets.push_back(p_recv);
        }
    }
}