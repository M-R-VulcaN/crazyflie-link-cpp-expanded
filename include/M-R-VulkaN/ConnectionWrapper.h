#pragma once

#include <iostream>
#include "ConnectionWorker.h"

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

    ConnectionWorker* _conWorkerPtr;

public:
    ConnectionWrapper(ConnectionWorker& conWorker);

    ConnectionWrapper& operator=(bitcraze::crazyflieLinkCpp::Connection& con);

    // bitcraze::crazyflieLinkCpp::Packet recvFilteredData(int timeout, int port, int channel) const ;

    // // returns the data only from the same port and channel as the current _packet
    // bitcraze::crazyflieLinkCpp::Packet recvFilteredData(int timeout) const;
     template <class ValToSend>
    bitcraze::crazyflieLinkCpp::Packet sendRecvData(int timeout, const ValToSend& dataToSend, size_t sizeOfDataToSend = 0) const
   {
        std::mutex mu;
        std::unique_lock<std::mutex> lock(mu);
        std::condition_variable waitForRecv;
        std::condition_variable *waitForRecvPtr = &waitForRecv;
        std::atomic<bool> isResultReturned( false);
        std::atomic<bool>* isResultReturnedPtr = &isResultReturned;
        // std::cout << "test" << std::endl;
        bitcraze::crazyflieLinkCpp::Packet res;
        bitcraze::crazyflieLinkCpp::Packet *resPtr = &res;
        PacketCallbackBundle callbackBundle= {this->_port,this->_channel,(PacketCallback)[resPtr,waitForRecvPtr, isResultReturnedPtr](bitcraze::crazyflieLinkCpp::Packet p_recv){ 
            *resPtr = p_recv;
            waitForRecvPtr->notify_all();
            *isResultReturnedPtr = true;
            return false;}};
        _conWorkerPtr->addCallback(callbackBundle);
        if(sizeOfDataToSend > 0) 
        {
            _conWorkerPtr->send({(const uint8_t*)&dataToSend,sizeOfDataToSend});
        }       
        else
        {
            _conWorkerPtr->send({(const uint8_t*)&dataToSend,sizeof(dataToSend)});
        }
        if(0 == timeout)
        {
            waitForRecv.wait(lock ,[isResultReturnedPtr](){return (bool)*isResultReturnedPtr;});
        }
        else
        {
            waitForRecv.wait_for(lock,std::chrono::milliseconds(timeout) ,[isResultReturnedPtr](){return (bool)*isResultReturnedPtr;});
        }
        // std::cout << "test2 "<< res << std::endl;

        return res;
    }

    // bitcraze::crazyflieLinkCpp::Connection& getConnection();

    void setPort(int port);
    void setChannel(int channel);

    void sendData(const void* data1, const size_t& data1_len, const void* data2 = nullptr, const size_t& data2_len = 0) const;
    
    // //returns true if it was successful, else, false
    // template <typename ValType>
    // bool recvValue(ValType& result)
    // {
    //     // std::cout << (int)objectToSend << std::endl;
    //     auto p_recv = this->recvFilteredData(0);
    //     if(sizeof(result)<p_recv.payloadSize())
    //         return false;
    //     std::copy_n(p_recv.payload(),p_recv.payloadSize(),(uint8_t*)&result);
    //     return true;
    // }
    // //returns true if it was successful, else, false
    // bool recvFP16(float& result)
    // {
    //     auto p_recv = this->recvFilteredData(0);
    //     if(p_recv.payloadSize() != sizeof(uint16_t))
    //         return false;
    //     std::copy_n(p_recv.payload(),p_recv.payloadSize(),(uint8_t*)&result);
    //     return true;
    // }

    ~ConnectionWrapper();
};

class PacketData
{
    private:
    std::array<uint8_t,CRTP_MAXSIZE> _data;
    uint8_t _currIndex = 0;
    public:
    PacketData()
    {}
    ~PacketData()
    {}
    template <class T>
    PacketData(const T& data, const size_t& sizeOfData = 0)
    {
        this->appendData(data,sizeOfData);
    }  
    template <class T>
    void appendData(const T& data, const size_t& sizeOfData = 0)
    {
        uint8_t sizeToCopy;

        if(sizeOfData > 0)
            sizeToCopy = std::min({(uint8_t)sizeOfData,(uint8_t)(CRTP_MAXSIZE-_currIndex),(uint8_t)sizeof(data)});
        else
            sizeToCopy = std::min((uint8_t)sizeof(data),(uint8_t)(CRTP_MAXSIZE-_currIndex));

        std::copy_n( (uint8_t*)&data,_currIndex,_data);
        _currIndex += sizeToCopy;
    }
    std::array<uint8_t,CRTP_MAXSIZE> getData() const
    {
        return _data;
    }
    uint8_t size() const
    {
        return _currIndex+1;
    }
};