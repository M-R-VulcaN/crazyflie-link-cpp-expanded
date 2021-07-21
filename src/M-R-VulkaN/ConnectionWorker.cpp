#include "ConnectionWorker.h"
#include <iostream>
using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;
ConnectionWorker::ConnectionWorker(Connection &con) 
{
    _conPtr = & con;
    
}
ConnectionWorker::~ConnectionWorker()
{
    _conPtr = nullptr;
}
void ConnectionWorker::start()
{
}
void ConnectionWorker::stop()
{
}
void ConnectionWorker::sendPacket(const Packet &packetToSend)
{
    
    std::cout << packetToSend;
}
Packet ConnectionWorker::recvPacket(uint8_t port, uint8_t channel)
{
    Packet p;
    p.setPort(port);
    p.setChannel(channel);
    return p;
}

void ConnectionWorker::sendPacketsThreadFunc()
{

}
void ConnectionWorker::receivePacketsThreadFunc()
{

}