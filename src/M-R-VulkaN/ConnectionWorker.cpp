#include "ConnectionWorker.h"
#include <iostream>
#include <chrono>
// #include <atomic>

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;
ConnectionWorker::ConnectionWorker(Connection &con)
{
    _conPtr = &con;
    _receivingThread = std::thread(&ConnectionWorker::receivePacketsThreadFunc, this);

    _threadsActiveFlag = false;
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
        // this->debugPrint("pass recv");

        {
            // std::lock_guard<std::mutex> lock(_conMutex);
            p_recv = _conPtr->recv(100);
        std::cout <<("pass recv1")<<std::endl;

        }
        if (p_recv && _threadsActiveFlag)
        {
        std::cout <<("pass recv1")<<std::endl;

            std::lock_guard<std::mutex> lock(_packetRecvMutex);
            _receivedPackets.push_back(p_recv);
        }
    }
}