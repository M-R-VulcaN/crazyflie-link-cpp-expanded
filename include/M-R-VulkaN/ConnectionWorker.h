#pragma once

#include <queue>
#include <list>
#include <thread>
#include <mutex>
#include "Connection.h"
#include "Packet.hpp"

class ConnectionWorker
{
private:
    std::queue<bitcraze::crazyflieLinkCpp::Packet> _sendPackets;
    std::list<bitcraze::crazyflieLinkCpp::Packet> _receivedPackets;
    std::thread _sendingThread;
    std::thread _receivingThread;
    std::mutex _conMutex;
    bitcraze::crazyflieLinkCpp::Connection* _conPtr;

    void sendPacketsThreadFunc();   
    void receivePacketsThreadFunc();   
public:
    ConnectionWorker(bitcraze::crazyflieLinkCpp::Connection& con);
    ~ConnectionWorker();
    void start();
    void stop();
    void sendPacket(const bitcraze::crazyflieLinkCpp::Packet& packetToSend);
    bitcraze::crazyflieLinkCpp::Packet recvPacket(uint8_t port, uint8_t channel);
};

