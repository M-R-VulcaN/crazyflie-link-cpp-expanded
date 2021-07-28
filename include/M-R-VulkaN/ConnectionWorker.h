#pragma once

#include <queue>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Connection.h"
#include "Packet.hpp"
#include <functional>
#include <atomic>

typedef void (*PacketCallbackFunc)(bitcraze::crazyflieLinkCpp::Packet);

// class IPacketCallback
// {
//     public:
//     virtual void operator()(bitcraze::crazyflieLinkCpp::Packet p_recv) = 0;

// };

// template<class Func>
struct PacketCallbackBundle
{
    uint8_t _port;
    uint8_t _channel;
    std::function<bool(bitcraze::crazyflieLinkCpp::Packet)> _packetCallbackFunc;
};

class ConnectionWorker
{
private:
    std::list<bitcraze::crazyflieLinkCpp::Packet> _receivedPackets;
    std::list<PacketCallbackBundle> _paramReceivedCallbacks;
    std::thread _receivingThread;
    std::mutex _packetRecvMutex;
    std::mutex _threadSleepMutex;
    std::condition_variable _threadSleepConVar;
    bitcraze::crazyflieLinkCpp::Connection *_conPtr;
    std::atomic<bool> _deactivateThread;
    std::atomic<bool> _isThreadSleeping;
    void receivePacketsThreadFunc();

public:
    ConnectionWorker(bitcraze::crazyflieLinkCpp::Connection &con);
    ~ConnectionWorker();
    void start();
    void stop();
    void addCallback(const PacketCallbackBundle &callback);
    bitcraze::crazyflieLinkCpp::Packet recv(uint8_t port, uint8_t channel, unsigned long timeout = UINT64_MAX);
    void send(const bitcraze::crazyflieLinkCpp::Packet& p);
    // bitcraze::crazyflieLinkCpp::Packet recvPacket(uint8_t port, uint8_t channel);
};
