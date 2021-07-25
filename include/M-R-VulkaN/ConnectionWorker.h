#pragma once

#include <queue>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Connection.h"
#include "Packet.hpp"

class ConnectionWorker
{
private:
    std::list<bitcraze::crazyflieLinkCpp::Packet> _receivedPackets;
    std::thread _receivingThread;
    std::mutex _packetRecvMutex;
    bitcraze::crazyflieLinkCpp::Connection *_conPtr;
    bool _threadsActiveFlag;
    void receivePacketsThreadFunc();

public:
    ConnectionWorker(bitcraze::crazyflieLinkCpp::Connection &con);
    ~ConnectionWorker();
    void start();
    void stop();
    bitcraze::crazyflieLinkCpp::Packet recvPacket(uint8_t port, uint8_t channel);
};
