#pragma once
#include <errno.h>

#include "Toc.h"
#include "ConnectionWrapper.h"

#define CONTROL_CREATE_BLOCK_V2 6


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

};
