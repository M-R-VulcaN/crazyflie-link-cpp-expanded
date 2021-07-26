#pragma once

#include <queue>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Connection.h"
#include "Packet.hpp"
#include <functional>

typedef void (*PacketCallbackFunc)(bitcraze::crazyflieLinkCpp::Packet);

// class IPacketCallback
// {
//     public:
//     virtual void operator()(bitcraze::crazyflieLinkCpp::Packet p_recv) = 0;
    
// };


struct PacketCallbackBundle
{
    uint8_t _port;
    uint8_t _channel;
    std::function<void(bitcraze::crazyflieLinkCpp::Packet)> & _packetCallbackFunc;
};

class ConnectionWorker
{
private:
    std::list<bitcraze::crazyflieLinkCpp::Packet> _receivedPackets;
    std::vector<PacketCallbackBundle> _paramReceivedCallbacks;
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
    void addCallback(const PacketCallbackBundle& callback);
    // bitcraze::crazyflieLinkCpp::Packet recvPacket(uint8_t port, uint8_t channel);
};
