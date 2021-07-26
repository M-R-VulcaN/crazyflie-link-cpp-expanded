#include "Crazyflie.h"
using namespace bitcraze::crazyflieLinkCpp;

Crazyflie::Crazyflie(const std::string &uri) : _con(uri), _conWrapperParamRead(_con), _conWrapperParamWrite(_con), _conWrapperParamToc(_con), _conWrapperLogToc(_con), _conWrapperAppchannel(_con), _logTocWpr(_logToc,_conWrapperLogToc), _paramTocWpr(_paramToc, _conWrapperParamToc), _conWorker(_con)
{
    _isRunning = false;
   
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

Connection& Crazyflie::getCon()
{return _con;}


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

double Crazyflie::getDoubleFromCrazyflie(uint16_t paramId) const
{
    double res = 0;
    
    _conWrapperParamRead.sendData(&paramId, sizeof(paramId));
    Packet p = _conWrapperParamRead.recvFilteredData(0);
    std::memcpy(&res, p.payload() + PAYLOAD_VALUE_BEGINING_INDEX, sizeof(res));
    
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


//print the TOC with values!
void Crazyflie::printParamToc() const
{
    auto tocItemsVector = _paramToc.getAllTocItems();

    for (TocItem tocItem : tocItemsVector)
    {
        std::cout << tocItem;
        if (to_string(tocItem._type).find("int") != std::string::npos)
        {
            std::cout << getUIntFromCrazyflie(tocItem._id) << std::endl;}
        else
            std::cout << getFloatFromCrazyflie(tocItem._id) << std::endl;
    }
    std::cout << "Printed " << tocItemsVector.size() << " items total" << std::endl;
}


/*
save the TOC with values to a csv file.
input: path = the requested path.
       fileName = the requested file name. 
*/
void Crazyflie::csvParamToc(std::string path,std::string fileName) const
{
    std::string filepath = path + "/" + fileName;
    std::ofstream file;   
    file.open(filepath); 

    auto tocItemsVector = _paramToc.getAllTocItems();

    for (TocItem tocItem : tocItemsVector)
    {
        //tocParamsFile << tocItem;
        file << (unsigned int)tocItem._id << "," << to_string(tocItem._accessType) << "," << to_string(tocItem._type) << "," << tocItem._groupName << "," << tocItem._name << ",";
        if (to_string(tocItem._type).find("int") != std::string::npos)
        {
            file << getUIntFromCrazyflie(tocItem._id) << std::endl;}
        else
            file << getFloatFromCrazyflie(tocItem._id) << std::endl;
    }
    std::cout << "saved " << tocItemsVector.size() << " parameters to a .csv file under the path: " << filepath << std::endl;
    file.close();
}

//print the TOC
void Crazyflie::printLogToc() const
{
    auto tocItemsVector = _logToc.getAllTocItems();

    for (TocItem tocItem : tocItemsVector)
    {
        std::cout << tocItem <<std::endl;
    }
    std::cout << "Printed " << tocItemsVector.size() << " items total" << std::endl;
    std::cout << "=========================================================================" << std::endl;
}

bool Crazyflie::init()
{
     _conWrapperLogToc.setPort(LOG_PORT);

    _conWrapperParamToc.setPort(PARAM_PORT);
    _conWrapperParamRead.setPort(PARAM_PORT);
    _conWrapperParamWrite.setPort(PARAM_PORT);
    _conWrapperAppchannel.setPort(APPCHANNEL_PORT);

    _conWrapperLogToc.setChannel(TOC_CHANNEL_LOG);
    _conWrapperParamToc.setChannel(TOC_CHANNEL_PARAM);
    _conWrapperParamRead.setChannel(PARAM_READ_CHANNEL);
    _conWrapperParamWrite.setChannel(PARAM_WRITE_CHANNEL);
    _conWrapperAppchannel.setChannel(APP_CHANNEL);

    _logTocWpr.initToc();

    _paramTocWpr.initToc();

    _isRunning = true;
    _conWorker.start();
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
/*
        {0x08, "uint8_t"},
        {0x09, "uint16_t"},
        {0x0A, "uint32_t"},
        {0x0B, "uint64_t"},
        {0x00, "int8_t"},
        {0x01, "int16_t"},
        {0x02, "int32_t"},
        {0x03, "int64_t"},
        {0x05, "FP16"},
        {0x06, "float"},
        {0x07, "double"}};
*/
std::vector<std::pair<TocItem, ParamValue>> Crazyflie::getTocAndValues() const
{
    std::vector<std::pair<TocItem, ParamValue>> res;

    auto tocItems = _paramToc.getAllTocItems();

    for (TocItem tocItem : tocItems)
    {
        ParamValue val;
        if (tocItem._type == "float")
        {
            val._floatVal = this->getFloatFromCrazyflie(tocItem._id);
        }
        else if (tocItem._type == "uint32_t")
        {
            val._floatVal = this->getUIntFromCrazyflie(tocItem._id);
        }

        res.emplace_back(tocItem, val);
    }
    return res;
}

void Crazyflie::addParamReceivedCallback( const ParamValueCallback& callback)
{
    _paramReceivedCallbacks.push_back(callback);
}

void Crazyflie::addLogCallback( const LogBlockReceivedCallback& callback)
{
    auto func = (std::function<void (bitcraze::crazyflieLinkCpp::Packet)> )[callback](Packet p_recv){
        if(p_recv)
        callback(Packet(p_recv));
    // std::this_thread::sleep_for(std::chrono::seconds(3));

    };
    _conWorker.addCallback({5,2, func});
}

void Crazyflie::addConsoleCallback( const ConsoleCallback& callback)
{

    auto func = (std::function<void (bitcraze::crazyflieLinkCpp::Packet)> )[callback](Packet p_recv){
        char data_str[33] = {0};
        data_str[p_recv.payloadSize()] = 0;
        std::memcpy(data_str,p_recv.payload(),p_recv.payloadSize());
        callback(data_str);
      
    };
    _conWorker.addCallback({0,0, func});
}
void Crazyflie::paramRecvThreadFunc()
{
    // _
    // for(auto callback : _paramReceivedCallbacks)
    // {
    //     callback()
    // }
}

const Toc& Crazyflie::getParamToc() const
{
    return _paramToc;
}
const Toc& Crazyflie::getLogToc() const
{
    return _logToc;
}