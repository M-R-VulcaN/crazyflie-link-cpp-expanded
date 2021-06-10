#include "Crazyflie.h"
using namespace bitcraze::crazyflieLinkCpp;

Crazyflie::Crazyflie(const std::string &uri) : _con(uri), _conWrapperParamRead(_con), _conWrapperParamWrite(_con), _conWrapperParamToc(_con), _conWrapperLogToc(_con), _conWrapperAppchannel(_con) 
{
    _isRunning = false;
    _conWrapperLogToc.setPort(LOG_PORT);

    _conWrapperParamToc.setPort(PARAM_PORT);
    _conWrapperParamRead.setPort(PARAM_PORT);
    _conWrapperParamWrite.setPort(PARAM_PORT);
    _conWrapperAppchannel.setPort(APPCHANNEL_PORT);

    _conWrapperLogToc.setPort(TOC_CHANNEL_LOG);
    _conWrapperParamToc.setChannel(TOC_CHANNEL_PARAM);
    _conWrapperParamRead.setChannel(PARAM_READ_CHANNEL);
    _conWrapperParamWrite.setChannel(PARAM_WRITE_CHANNEL);
    _conWrapperAppchannel.setChannel(APP_CHANNEL);
}

void Crazyflie::sendAppChannelData(const void *data, const size_t &dataLen)
{
    _conWrapperAppchannel.sendData(data, dataLen);
}

std::vector<uint8_t> Crazyflie::recvAppChannelData()
{
    Packet p = _conWrapperAppchannel.recvFilteredData(0);
    std::vector<uint8_t> res;

    if(!p)
    {
        return res;
    }
    std::copy(p.payload(), p.payload() + p.payloadSize(), std::back_inserter(res));
    return res;
}

size_t Crazyflie::recvAppChannelData(void* dest, const size_t& dataLen)
{
    Packet p = _conWrapperAppchannel.recvFilteredData(0);
    std::vector<uint8_t> res;
    size_t sizeToWrite = std::max(dataLen,p.payloadSize());
    if(p)
    {
        std::copy_n(p.payload(), sizeToWrite, (uint8_t*)dest);
    }
    return sizeToWrite;
}

float Crazyflie::getFloatFromCrazyflie(uint16_t paramId) const
{
    float res = 0;

    _conWrapperParamRead.sendData(&paramId, sizeof(paramId));
    Packet p = _conWrapperParamRead.recvFilteredData(0);
    std::memcpy(&res, p.payload() + PAYLOAD_VALUE_BEGINING_INDEX, sizeof(res));

    return res;
}

uint32_t Crazyflie::getUIntFromCrazyflie(uint16_t paramId) const
{
    uint32_t res = 0;
    _conWrapperParamRead.sendData(&paramId, sizeof(paramId));

    Packet p = _conWrapperParamRead.recvFilteredData(0);

    std::memcpy(&res, p.payload() + PAYLOAD_VALUE_BEGINING_INDEX, p.payloadSize() - PAYLOAD_VALUE_BEGINING_INDEX);

    return res;
}

float Crazyflie::getFloatByName(const std::string &group, const std::string &name) const
{
    return getFloatFromCrazyflie(_paramToc.getItemId(group, name));
}

uint32_t Crazyflie::getUIntByName(const std::string &group, const std::string &name) const
{
    return getUIntFromCrazyflie(_paramToc.getItemId(group, name));
}

Crazyflie::~Crazyflie()
{
}

bool Crazyflie::setParamInCrazyflie(uint16_t paramId, float newValue)
{
    _conWrapperParamWrite.sendData(&paramId, sizeof(paramId), &newValue, sizeof(newValue));

    return true;
}

bool Crazyflie::setParamInCrazyflie(uint16_t paramId, uint32_t newValue, const size_t &valueSize)
{
    _conWrapperParamWrite.sendData(&paramId, sizeof(paramId), &newValue, valueSize);

    return true;
}

void Crazyflie::initParamToc()
{
    // ask for the toc info
    uint8_t cmd = CMD_TOC_INFO_V2;
    _conWrapperParamToc.sendData(&cmd, sizeof(cmd));
    Packet p_recv = _conWrapperParamToc.recvFilteredData(0);
    TocInfo cfTocInfo(p_recv);

    uint16_t num_of_elements = cfTocInfo._numberOfElements;

    for (uint16_t i = 0; i < num_of_elements; i++)
    {
        TocItem tocItem();
        _paramToc.insert(getTocItemFromCrazyflie(i));
    }
}

void Crazyflie::initLogToc()
{
    // ask for the toc info
    uint8_t cmd = CMD_TOC_INFO_V2;
    _conWrapperLogToc.sendData(&cmd, sizeof(cmd));
    Packet p_recv = _conWrapperLogToc.recvFilteredData(0);
    TocInfo cfTocInfo(p_recv);

    uint16_t num_of_elements = cfTocInfo._numberOfElements;

    for (uint16_t i = 0; i < num_of_elements; i++)
    {
        TocItem tocItem();
        _logToc.insert(getTocItemFromCrazyflie(i));
    }
}

TocItem Crazyflie::getTocItemFromCrazyflie(uint16_t id) const
{
    uint8_t cmd = CMD_TOC_ITEM_V2;
    // ask for a param with the given id
    _conWrapperParamToc.sendData(&cmd, sizeof(uint8_t), &id, sizeof(id));
    Packet p_recv = _conWrapperParamToc.recvFilteredData(0);

    return TocItem(p_recv);
}

// //print the TOC with values!
void Crazyflie::printParamToc() const
{
    auto tocItemsVector = _paramToc.getAllTocItems();

    for (TocItem tocItem : tocItemsVector)
    {
        std::cout << tocItem;
        if (to_string(tocItem._Type).find("int") != std::string::npos)
            std::cout << getUIntFromCrazyflie(tocItem._Id) << std::endl;
        else
            std::cout << getFloatFromCrazyflie(tocItem._Id) << std::endl;
    }
    std::cout << "Printed " << tocItemsVector.size() << " items total" << std::endl;
}

// //print the TOC with values!
void Crazyflie::printLogToc() const
{
    auto tocItemsVector = _logToc.getAllTocItems();

    for (TocItem tocItem : tocItemsVector)
    {
        std::cout << tocItem;
        if (to_string(tocItem._Type).find("int") != std::string::npos)
            std::cout << getUIntFromCrazyflie(tocItem._Id) << std::endl;
        else
            std::cout << getFloatFromCrazyflie(tocItem._Id) << std::endl;
    }
    std::cout << "Printed " << tocItemsVector.size() << " items total" << std::endl;
}

bool Crazyflie::init()
{
    initParamToc();
    initLogToc();
    _isRunning = true;
    return true;
}
bool Crazyflie::isRunning() const
{
    return _isRunning;
}

bool Crazyflie::setParamByName(const std::string &group, const std::string &name, float newValue)
{
    return setParamInCrazyflie(_paramToc.getItemId(group, name), newValue);
}
bool Crazyflie::setParamByName(const std::string &group, const std::string &name, uint32_t newValue, const size_t &valueSize)
{
    return setParamInCrazyflie(_paramToc.getItemId(group, name), newValue, valueSize);
}
bool Crazyflie::isParamFloat(const std::string &group, const std::string &name) const
{
    return _paramToc.getItem(group, name).isFloat();
}

std::vector<std::pair<TocItem, ParamValue>> Crazyflie::getTocAndValues() const
{
    std::vector<std::pair<TocItem, ParamValue>> res;

    auto tocItems = _paramToc.getAllTocItems();

    for (TocItem tocItem : tocItems)
    {
        ParamValue val;
        if (tocItem.isFloat())
        {
            val._floatVal = this->getFloatFromCrazyflie(tocItem._Id);
        }
        else
        {
            val._floatVal = this->getUIntFromCrazyflie(tocItem._Id);
        }

        res.emplace_back(tocItem, val);
    }
    return res;
}
