#include "Log.h"

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;
Log::Log(Toc &toc, Connection& con) : _tocPtr(&toc), _conWpr(con)
{
}

Log::~Log()
{
}

int Log::createLogBlock(uint8_t logType, uint16_t logId)
{
    uint16_t i = 0;
    uint8_t data[] = {CONTROL_CREATE_BLOCK_V2, 0,logType, (uint8_t)(logId & 0xff),(uint8_t)(logId >> 8)};
    uint8_t failCode = 0;

    for (i = 0; i < UINT8_MAX; i++)
    {
        if (!idsOccupied[i])
        {
            idsOccupied[i] = true;
            data[1] = i;
            _conWpr.sendData(data, 5);
            Packet p_recv = _conWpr.recvFilteredData(0);
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
