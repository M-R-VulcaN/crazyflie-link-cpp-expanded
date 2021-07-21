#include "ConnectionWorker.h"
#include <iostream>
#include <chrono>
// #include <atomic>

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;
ConnectionWorker::ConnectionWorker(Connection &con)
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
}
void ConnectionWorker::start()
{
    _threadsActiveFlag = true;
}
void ConnectionWorker::stop()
{
    _threadsActiveFlag = false;
}
void ConnectionWorker::sendPacket(const Packet &packetToSend)
{
    std::lock_guard<std::mutex> lock(_packetSendMutex);
    _sendPackets.push(packetToSend);
}
Packet ConnectionWorker::recvPacket(uint8_t port, uint8_t channel)
{
    for (auto it = _receivedPackets.begin(); it != _receivedPackets.end(); it++)
    {
        if (it->channel() == channel && it->port() == port)
        {
            std::lock_guard<std::mutex> lock(_packetRecvMutex);
            Packet p = *it;
            _receivedPackets.erase(it);
            return p;
        }
    }
    return Packet();
}

void ConnectionWorker::sendPacketsThreadFunc()
{
    // std::atomic
    const auto& list = _receivedPackets;
    while (true)
    {
        while (!_threadsActiveFlag)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::unique_lock<std::mutex> packetsToSendLock(_packetSendMutex);
        _packetSendConditionVariable.wait_until(packetsToSendLock, 
        std::chrono::system_clock::now() , [list](){return !list.empty();});

        Packet p_recv;
        {
            std::lock_guard<std::mutex> lock(_conMutex);
            p_recv = _conPtr->recv(2);
        }
        if (!p_recv)
            continue;
        {
            std::lock_guard<std::mutex> lock(_packetRecvMutex);
            _receivedPackets.push_back(p_recv);
        }
    }
}
void ConnectionWorker::receivePacketsThreadFunc()
{
        while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        while (!_threadsActiveFlag)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        Packet p_recv;
        {
            std::lock_guard<std::mutex> lock(_conMutex);
            p_recv = _conPtr->recv(2);
        }
        if (!p_recv)
            continue;
        {
            std::lock_guard<std::mutex> lock(_packetRecvMutex);
            _receivedPackets.push_back(p_recv);
        }
    }
}