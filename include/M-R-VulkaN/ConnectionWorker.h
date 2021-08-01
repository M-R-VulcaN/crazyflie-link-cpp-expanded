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
    std::list<PacketCallbackBundle> _paramReceivedCallbacks;
    std::thread _receivingThread;
    std::mutex _threadSleepMutex;

    std::condition_variable _threadSleepConVar;
    std::atomic<bitcraze::crazyflieLinkCpp::Connection *> _conAtomicPtr;
    std::atomic<bool> _deactivateThread;
    void receivePacketsThreadFunc();

public:
    ConnectionWorker(bitcraze::crazyflieLinkCpp::Connection &con);
    ~ConnectionWorker();
    void start();
    void stop();
    void addCallback(const PacketCallbackBundle &callback);
    void send(const bitcraze::crazyflieLinkCpp::Packet &p);
    std::mutex &getRecvMutex();
    std::mutex &getPostRecvMutex();
};
