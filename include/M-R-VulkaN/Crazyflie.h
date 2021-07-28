#pragma once

#include <map>
#include <vector>
#include <thread>
#include <fstream> //for saving .csv file

#include "ConnectionWrapper.h"
#include "TocWrapper.h"
#include "ConnectionWorker.h"

#define PAYLOAD_VALUE_BEGINING_INDEX 3
#define NOT_FOUND 0

#define APP_CHANNEL 2

#define TOC_CHANNEL_LOG 0         //	Table of content access: Used for reading out the TOC

#define TOC_CHANNEL_PARAM 0
#define PARAM_READ_CHANNEL 1
#define PARAM_WRITE_CHANNEL 2

#define LOG_CONTROL_CHANNEL 1     //	Log control: Used for adding/removing/starting/pausing log blocks
#define LOG_DATA_CHANNEL 2       // 	Log data: Used to send log data from the Crazyflie to the client

#define PARAM_PORT 2
#define LOG_PORT 5
#define APPCHANNEL_PORT 13

typedef bool (*ParamValueCallback)(const ParamValue&);
typedef bool (*ConsoleCallback)(const char*);
typedef bool (*LogBlockReceivedCallback)(const bitcraze::crazyflieLinkCpp::Packet&);

class Crazyflie
{
private:
    Toc _paramToc;
    Toc _logToc;
    
    bitcraze::crazyflieLinkCpp::Connection _con;
    ConnectionWrapper _conWrapperParamRead;
    ConnectionWrapper _conWrapperParamWrite;
    ConnectionWrapper _conWrapperParamToc;
    ConnectionWrapper _conWrapperLogToc;
    ConnectionWrapper _conWrapperAppchannel;
    TocWrapper _logTocWpr;
    TocWrapper _paramTocWpr;
    bool _isRunning;
    std::vector<ParamValueCallback> _paramReceivedCallbacks;
    std::vector<ConsoleCallback> _consoleCallbacks;
    std::thread _paramRecvThread;

    public:
    ConnectionWorker _conWorker;
    private:
    
    bool setParamInCrazyflie(uint16_t paramId, float newValue);
    bool setParamInCrazyflie(uint16_t paramId, uint32_t newValue, const size_t &valueSize);
    template <class Val>
    Val getParamValFromCrazyflie(uint16_t paramId) const
    {
          Val res = 0;
    _conWrapperParamRead.sendData(&paramId, sizeof(paramId));

    bitcraze::crazyflieLinkCpp::Packet p = _conWrapperParamRead.recvFilteredData(0);

    std::memcpy(&res, p.payload() + PAYLOAD_VALUE_BEGINING_INDEX, std::min(sizeof(res),p.payloadSize() - PAYLOAD_VALUE_BEGINING_INDEX));

    return res;
    }
    float getFloatFromCrazyflie(uint16_t paramId) const;
    void initParamToc();
    void initLogToc();

    void paramRecvThreadFunc();
public:
    void addParamReceivedCallback( const ParamValueCallback& callback);
    void addConsoleCallback( const ConsoleCallback& callback);
    void addLogCallback( const LogBlockReceivedCallback& callback);
    Crazyflie(const std::string &uri);
    ~Crazyflie();
    bool isRunning() const;
    bool init();
    bitcraze::crazyflieLinkCpp::Connection& getCon();
    
    uint32_t getUIntByName(const std::string &group, const std::string &name) const;
    float getFloatByName(const std::string &group, const std::string &name) const;

    bool setParamByName(const std::string &group, const std::string &name, float newValue);
    bool setParamByName(const std::string &group, const std::string &name, uint32_t newValue, const size_t &valueSize);
    const Toc& getParamToc() const;
    const Toc& getLogToc() const;
    void printParamToc() const;
    void csvParamToc(std::string path,std::string fileName) const;
    void printLogToc() const;
    std::vector<std::pair<TocItem, ParamValue>> getTocAndValues() const;

    void sendAppChannelData(const void *data, const size_t &dataLen);
    std::vector<uint8_t> recvAppChannelData();
    //returns the amount of bytes it wrote
    size_t recvAppChannelData(void* dest, const size_t& dataLen);

    //**************************************
    //todo: add callback for param changed
    //todo: console
    //**************************************
};
