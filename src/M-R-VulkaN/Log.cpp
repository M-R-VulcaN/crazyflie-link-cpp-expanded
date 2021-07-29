#include "Log.h"

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;
Log::Log(Toc &toc, ConnectionWorker &conWorker) : _tocPtr(&toc), _conWpr(conWorker)
{
}

Log::~Log()
{
}

int Log::createLogBlock(uint8_t logType, uint16_t logId)
{
    uint16_t i = 0;
    uint8_t data[] = {CONTROL_CREATE_BLOCK_V2, 0, logType, (uint8_t)(logId & 0xff), (uint8_t)(logId >> 8)};
    uint8_t failCode = 0;
    for (i = 0; i < UINT8_MAX; i++)
    {
        if (!idsOccupied[i])
        {
            idsOccupied[i] = true;
            data[1] = i;
            // _conWpr.sendData(data, 5);
            Packet p_recv = _conWpr.sendRecvData(0, data);
            failCode = p_recv.payload()[2];
            if (17 == failCode)
                continue;
            break;
        }
    }

    if (0 == failCode)
    {
        std::cout << "Success! id = " << (int)i << std::endl;
    }
    else
    {
        std::cout << "Failiure! code = " << (int)failCode << std::endl;
    }
    return 0;
}

int Log::deleteLogBlock(uint8_t id)
{
    uint8_t data[2] = {0};

    data[0] = CONTROL_DELETE_BLOCK_V2;
    data[1] = id;

    uint8_t failCode = 0;

    for (uint16_t i = 0; i < UINT8_MAX; i++)
    {
        if (!idsOccupied[i])
        {
            // idsOccupied[i] = true;
            // data[1] = i;
            // _conWpr.sendData(data, 2);
            Packet p_recv = _conWpr.sendRecvData(0, data);
            failCode = p_recv.payload()[2];
            if (17 == failCode)
                continue;
            break;
        }
    }

    if (0 == failCode)
    {
        std::cout << "Success! deleted block id = " << (int)data[1] << std::endl;
    }
    else
    {
        std::cout << "Failiure! code = " << (int)failCode << std::endl;
    }
    return 0;
}

int Log::appendLogBlock(uint8_t logType, uint16_t logId)
{
    return logType + logId;
}
int Log::startLogBlock(uint8_t id)
{
    return id;
}
int Log::stopLogBlock(uint8_t id)
{
    return id;
}
int Log::resetLogBlocks()
{
    return 0;
}