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



//The PacketCallback returns a boolean,
//If it returns true then the callback will be called for another loop
//If it returns false then the callback is removed from the list
typedef std::function<bool(bitcraze::crazyflieLinkCpp::Packet)> PacketCallback;

//Includes the port and channel of the callback
struct PacketCallbackBundle
{
    uint8_t _port;
    uint8_t _channel;
    PacketCallback _packetCallbackFunc;
};

//This class is the main worker class that is responsible for sending callbacks
// on received packets from the crazyflie server
//It is also a thin rapper around the Connection class 
class ConnectionWorker
{
private:
    std::list<PacketCallbackBundle> _paramReceivedCallbacks;//The list of callbacks that are present
    std::thread _receivingThread;//The mutex for receiving packets
    std::mutex _threadSleepMutex; //The mutex for changing the receive-thread's state from active to inactive or vice versa
    std::mutex _callbackMutex; // The mutex for running a callback function
    std::shared_timed_mutex _callbackSharedMutex;

    std::condition_variable _threadSleepConVar; //Condition variable which is used for waiting whenever the receive-thread is sleeping
    std::atomic<bitcraze::crazyflieLinkCpp::Connection *> _conAtomicPtr; // An atomic pointer to the Connection object so that you could do multi-thread activities on it
    std::atomic<bool> _deactivateThread; //a switch for activating or deactivated the thread
    void receivePacketsThreadFunc();//Todo: create a thread each new callback

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
