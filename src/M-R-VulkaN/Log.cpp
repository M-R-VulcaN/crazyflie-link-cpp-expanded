#include "Log.h"
#include <errno.h>
using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;
Log::Log(Toc &toc, ConnectionWorker &conWorker) : _tocPtr(&toc), _conWpr(conWorker)
{
    _conWpr.setPort(CRTP_PORT_LOG);
    _conWpr.setChannel(CONTROL_CH);
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
            Packet p_recv = _conWpr.sendRecvData(0, data);
            failCode = p_recv.payload()[2];
            if (EEXIST == failCode)
                continue;

            if (LOG_SUCCESS == failCode)
            {
                _logBlocks.insert({i,{_tocPtr->getItem(logId)}});
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
    
    if (true) //idsOccupied[id] != OccupiedStatus::OCCUPIED)
    {
        uint8_t data[] = {CONTROL_CREATE_BLOCK_V2, id, logType, (uint8_t)(logId & 0xff), (uint8_t)(logId >> 8)};

        uint8_t failCode = 0;

        Packet p_recv = _conWpr.sendRecvData(0, data);
        failCode = p_recv.payload()[2];
        if (LOG_SUCCESS == failCode)
        {
            _logBlocks.insert({id,{_tocPtr->getItem(logId)}});
            idsOccupied[id] = OccupiedStatus::OCCUPIED;
            return id;
        }
        // for (i = 0; i < UINT8_MAX; i++)
        //         {
        //             if (!idsOccupied[i])
        //             {
        //                 idsOccupied[i] = true;
        //                 data[1] = i;
        //                 conWpr.sendData(data, 5);
        //                 Packet p_recv = conWpr.recvFilteredData(0);
        //                 std::cout << p_recv << std::endl;
        //                 failCode = p_recv.payload()[2];
                        // if (17 == failCode)
                        //     continue;
                        // break;
        //             }
        //         }
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
            _logBlocks.erase(id);

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
            _logBlocks[id].push_back(_tocPtr->getItem(logId));
            
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
    if(LOG_SUCCESS == failCode)
    {
        _logBlocks.clear();
    }
    return -failCode;
}

std::list<TocItem> Log::getLogBlock(uint8_t id) const
{
    auto res = _logBlocks.find(id);
    if(res == _logBlocks.end())
        return std::list<TocItem>();
    return res->second;
}