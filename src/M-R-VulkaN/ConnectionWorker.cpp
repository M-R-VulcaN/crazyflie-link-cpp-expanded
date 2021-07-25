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
void ConnectionWorker::addCallback(const PacketCallback& callback)
{
    std::cout << (int)callback._port << std::endl;
    std::cout << (int)callback._channel << std::endl;
    _paramReceivedCallbacks.push_back(callback);
}

// Packet ConnectionWorker::recvPacket(uint8_t port, uint8_t channel)
// {
//     Packet res;
//     for (auto it = _receivedPackets.begin(); it != _receivedPackets.end(); it++)
//     {
//         if (it->channel() == channel && it->port() == port)
//         {
//             std::lock_guard<std::mutex> lock(_packetRecvMutex);
//             res = *it;
//             _receivedPackets.erase(it);
//             break;
//         }
//     }
//     return res;
// }

void ConnectionWorker::receivePacketsThreadFunc()
{
    Packet p_recv;
    while (true)
    {
        while (!_threadsActiveFlag)
        {
             if(nullptr == _conPtr )
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        if(_conPtr)
            p_recv = _conPtr->recv(100);
        else
            break;
        
        if (p_recv && _threadsActiveFlag)
        {

            std::lock_guard<std::mutex> lock(_packetRecvMutex);
            for(auto callback : _paramReceivedCallbacks)
            {
                if( p_recv.channel()==callback._channel  && p_recv.port() == callback._port )
                {
                    callback._packetCallbackFunc(p_recv);
                }
            }
            _receivedPackets.push_back(p_recv);
        }
    }
}