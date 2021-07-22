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

void ConnectionWorker::sendPacketsThreadFunc()
{
    const std::queue<Packet> &sendPacketsQueueRef = _sendPackets;
    std::unique_lock<std::mutex> packetsToSendLock(_packetSendMutex, std::defer_lock);

    while (true)
    {
        while (!_threadsActiveFlag)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        packetsToSendLock.lock();
        _packetSendConditionVariable.wait_until(packetsToSendLock,
                                                std::chrono::system_clock::now(), [sendPacketsQueueRef]()
                                                { return !sendPacketsQueueRef.empty(); });
        Packet pToSend =                         
        {
            std::lock_guard<std::mutex> lock(_conMutex);
            _conPtr->send(_sendPackets.front());
        }

        _sendPackets.pop();
        packetsToSendLock.unlock();

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
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        {
            std::lock_guard<std::mutex> lock(_conMutex);
            p_recv = _conPtr->recv(2);
        }
        if (p_recv)
        {
            std::lock_guard<std::mutex> lock(_packetRecvMutex);
            _receivedPackets.push_back(p_recv);
        }
    }
}