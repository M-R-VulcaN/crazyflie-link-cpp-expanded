#include "ConnectionWorker.h"
#include <iostream>
#include <chrono>

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
void ConnectionWorker::addCallback(const PacketCallbackBundle& callback)
{
    _paramReceivedCallbacks.push_back(callback);
}

void ConnectionWorker::receivePacketsThreadFunc()
{
    Packet p_recv;
    while (true)
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        while (!_threadsActiveFlag)
        {
             if(nullptr == _conPtr )
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        // _conPtr->recv
        if(_conPtr)
            p_recv = _conPtr->recv(1);
        else
            break;
        
        if (p_recv && _threadsActiveFlag)
        {

            std::lock_guard<std::mutex> lock(_packetRecvMutex);
            for(auto it = _paramReceivedCallbacks.begin(); it != _paramReceivedCallbacks.end();it++)
            {
                if( p_recv.channel()==it->_channel  && it->_port == p_recv.port() )
                {
                    if(!it->_packetCallbackFunc(p_recv))
                    {
                        _paramReceivedCallbacks.erase(it);
                    }
                }
            }
            _receivedPackets.push_back(p_recv);
        }
    }
}