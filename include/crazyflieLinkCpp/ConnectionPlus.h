#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <sstream>
#include <queue>
#include <vector>
#include "Connection.h"

#define PAYLOAD_MAX_SIZE CRTP_MAXSIZE-2

#define PARAM_PORT 2




class ConnectionPlus : public bitcraze::crazyflieLinkCpp::Connection
{
private:
    bitcraze::crazyflieLinkCpp::Packet _packet;
public:
    ConnectionPlus(std::string uri);
    ~ConnectionPlus();

    void setPort(int port);
    void setChannel(int channel);
    void sendInt(uint8_t intigerToSend);
    void sendInt(uint8_t intigerToSend, uint16_t extraData);
    
    void sendInt(uint8_t intigerToSend, int port, int channel);
    void sendInt(uint8_t intigerToSend, uint16_t extraData, int port, int channel);

    template <typename ObjectToSendType>
    void sendObject(const ObjectToSendType& objectToSend)
    {
        std::cout << (int)objectToSend << std::endl;

        if(sizeof(ObjectToSendType) > PAYLOAD_MAX_SIZE)
            throw std::runtime_error("Object to large to send as a backage. Size: " + sizeof(objectToSend));
        _packet.setPayloadSize(sizeof(objectToSend));
        std::memcpy(_packet.payload(), &objectToSend, sizeof(objectToSend));

        this->send(_packet);
    }

};
