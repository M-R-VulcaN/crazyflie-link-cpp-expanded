#pragma once

#include <iostream>
#include "Connection.h"

#define PAYLOAD_MAX_SIZE CRTP_MAXSIZE - 2

struct TocItemMessage
{
    uint8_t _cmd;
    uint16_t _id;
};

bool isBigEndian();

const bool IS_BIG_ENDIAN = isBigEndian();
class ConnectionWrapper
{
private:
    uint8_t _port;
    uint8_t _channel;

    bitcraze::crazyflieLinkCpp::Connection* _conPtr;

public:
    ConnectionWrapper(bitcraze::crazyflieLinkCpp::Connection & con);

    ConnectionWrapper& operator=(bitcraze::crazyflieLinkCpp::Connection& con);

    bitcraze::crazyflieLinkCpp::Packet recvFilteredData(int timeout, int port, int channel) const ;

    // returns the data only from the same port and channel as the current _packet
    bitcraze::crazyflieLinkCpp::Packet recvFilteredData(int timeout) const;

    bitcraze::crazyflieLinkCpp::Connection& getConnection();

    void setPort(int port);
    void setChannel(int channel);

    void sendData(const void* data1, const size_t& data1_len, const void* data2 = nullptr, const size_t& data2_len = 0) const;

    //returns true if it was successful, else, false
    template <typename ValType>
    bool recvValue(ValType& result)
    {
        // std::cout << (int)objectToSend << std::endl;
        auto p_recv = this->recvFilteredData(0);
        if(sizeof(result)<p_recv.payloadSize())
            return false;
        std::copy_n(p_recv.payload(),p_recv.payloadSize(),(uint8_t*)&result);
        return true;
    }
    //returns true if it was successful, else, false
    bool recvFP16(float& result)
    {
        auto p_recv = this->recvFilteredData(0);
        if(p_recv.payloadSize() != sizeof(uint16_t))
            return false;
        std::copy_n(p_recv.payload(),p_recv.payloadSize(),(uint8_t*)&result);
        return true;
    }

    ~ConnectionWrapper();
};
