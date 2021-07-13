#pragma once

#include <map>
#include <fstream> //for saving .csv file
#include "ConnectionWrapper.h"
#include "TocWrapper.h"

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

    
    bool setParamInCrazyflie(uint16_t paramId, float newValue);
    bool setParamInCrazyflie(uint16_t paramId, uint32_t newValue, const size_t &valueSize);

    uint32_t getUIntFromCrazyflie(uint16_t paramId) const;
    float getFloatFromCrazyflie(uint16_t paramId) const;
    double getDoubleFromCrazyflie(uint16_t paramId) const;
    void initParamToc();
    void initLogToc();

public:
    Crazyflie(const std::string &uri);
    ~Crazyflie();
    bool isRunning() const;
    bool init();


    uint32_t getUIntByName(const std::string &group, const std::string &name) const;
    float getFloatByName(const std::string &group, const std::string &name) const;

    bool setParamByName(const std::string &group, const std::string &name, float newValue);
    bool setParamByName(const std::string &group, const std::string &name, uint32_t newValue, const size_t &valueSize);

    void printParamToc() const;
    void printLogToc() const;
    std::vector<std::pair<TocItem, ParamValue>> getTocAndValues() const;

    void sendAppChannelData(const void *data, const size_t &dataLen);
    std::vector<uint8_t> recvAppChannelData();
    //returns the amount of bytes it wrote
    size_t recvAppChannelData(void* dest, const size_t& dataLen);

    
    //todo: add callback for param changed
    //todo: console
};
