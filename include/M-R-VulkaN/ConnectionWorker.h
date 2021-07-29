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
typedef std::function<bool(bitcraze::crazyflieLinkCpp::Packet)> PacketCallback;
struct PacketCallbackBundle
{
    uint8_t _port;
    uint8_t _channel;
    PacketCallback _packetCallbackFunc;
};

class ConnectionWorker
{
private:
    std::list<bitcraze::crazyflieLinkCpp::Packet> _receivedPackets;
    std::list<PacketCallbackBundle> _paramReceivedCallbacks;
    std::thread _receivingThread;
    std::mutex _threadSleepMutex;
    // std::mutex _recvMutex;
    // std::mutex _postRecvMutex;
    // std::mutex _conMutex;
    std::condition_variable _threadSleepConVar;
    std::atomic<bitcraze::crazyflieLinkCpp::Connection*> _conAtomicPtr;
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
    std::mutex& getRecvMutex();
    std::mutex& getPostRecvMutex();
};
