#include "Log.h"
#include <errno.h>
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
        if (idsOccupied[i] != OccupiedStatus::OCCUPIED)
        {
            data[1] = i;
            // _conWpr.sendData(data, 5);
            Packet p_recv = _conWpr.sendRecvData(0, data);
            failCode = p_recv.payload()[2];
            if (EEXIST == failCode)
                continue;
            if (LOG_SUCCESS == failCode)
            {
                idsOccupied[i] = OccupiedStatus::OCCUPIED;
                return i;
            }
            return -failCode;
        }
    }
    return -GENERIC_LOG_ERROR;
}

int Log::createLogBlock(uint8_t id, uint8_t logType, uint16_t logId)
{
    if (idsOccupied[id] != OccupiedStatus::OCCUPIED)
    {
        uint8_t data[] = {CONTROL_CREATE_BLOCK_V2, id, logType, (uint8_t)(logId & 0xff), (uint8_t)(logId >> 8)};

        uint8_t failCode = 0;

        Packet p_recv = _conWpr.sendRecvData(0, data);
        failCode = p_recv.payload()[2];
        if (LOG_SUCCESS == failCode)
        {
            idsOccupied[id] = OccupiedStatus::OCCUPIED;
            return id;
        }
        return -failCode;
    }
    return -GENERIC_LOG_ERROR;
}

int Log::deleteLogBlock(uint8_t id)
{
    uint8_t data[] = {CONTROL_DELETE_BLOCK, id};

    uint8_t failCode = LOG_SUCCESS;

    if (idsOccupied[id] != OccupiedStatus::NOT_OCCUPIED)
    {
        Packet p_recv = _conWpr.sendRecvData(0, data);
        failCode = p_recv.payload()[2];
        if (ENOENT == failCode || 0 == failCode)
        {
            idsOccupied[id] = OccupiedStatus::NOT_OCCUPIED;
            return id;
        }
        return -failCode;
    }
    return -GENERIC_LOG_ERROR;
}

int Log::appendLogBlock(uint8_t id, uint8_t logType, uint16_t logId)
{
    uint8_t data[] = {CONTROL_APPEND_BLOCK_V2, id, logType, (uint8_t)(logId & 0xff), (uint8_t)(logId >> 8)};
    uint8_t failCode = 0;
    if (idsOccupied[id] != OccupiedStatus::NOT_OCCUPIED)
    {
        data[1] = id;
        Packet p_recv = _conWpr.sendRecvData(0, data);
        failCode = p_recv.payload()[2];
        if (LOG_SUCCESS == failCode)
        {
            idsOccupied[id] = OccupiedStatus::OCCUPIED;
            return id;
        }
        return -failCode;
    }
    return -GENERIC_LOG_ERROR;
}
int Log::startLogBlock(uint8_t id, uint8_t period)
{
    if (idsOccupied[id] != OccupiedStatus::NOT_OCCUPIED)
    {
        uint8_t data[] = {CONTROL_START_BLOCK, id, period};
        Packet p_recv = _conWpr.sendRecvData(0, data);
        uint8_t failCode = p_recv.payload()[2];
        if (LOG_SUCCESS == failCode)
        {
            idsOccupied[id] = OccupiedStatus::OCCUPIED;
            return id;
        }
        return -failCode;
    }
    return -GENERIC_LOG_ERROR;
}
int Log::stopLogBlock(uint8_t id)
{
    if (idsOccupied[id] != OccupiedStatus::NOT_OCCUPIED)
    {
        uint8_t data[] = {CONTROL_START_BLOCK, id};

        uint8_t failCode = 0;

        Packet p_recv = _conWpr.sendRecvData(0, data);
        failCode = p_recv.payload()[2];
        if (LOG_SUCCESS == failCode)
        {
            return id;
        }

        return -failCode;
    }
    return -GENERIC_LOG_ERROR;
}
int Log::resetLogBlocks()
{
    uint8_t data[] = {CONTROL_RESET};
    uint8_t failCode = 0;

    Packet p_recv = _conWpr.sendRecvData(0, data);
    failCode = p_recv.payload()[2];

    std::fill(idsOccupied, idsOccupied + UINT8_MAX, OccupiedStatus::NOT_OCCUPIED);
    return -failCode;
}