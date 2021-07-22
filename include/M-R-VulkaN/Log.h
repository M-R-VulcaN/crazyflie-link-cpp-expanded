#pragma once
#include <errno.h>

#include "Toc.h"
#include "ConnectionWrapper.h"

#define CONTROL_CREATE_BLOCK_V2 6
#define CONTROL_DELETE_BLOCK_V2 2


#define CONTROL_CH 1
#define CRTP_PORT_LOG 0x05
#define MAX_LEN_NAME 31


class Log
{
private:
    Toc* _tocPtr;
    ConnectionWrapper _conWpr;
    bool idsOccupied[UINT8_MAX] = {false};

public:
    Log(Toc& toc, bitcraze::crazyflieLinkCpp::Connection& con);
    ~Log();
    int createLogBlock(uint8_t logType,uint16_t logId);
    int deleteLogBlock(uint16_t id);

};
