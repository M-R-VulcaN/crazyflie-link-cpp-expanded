#pragma once
#include <errno.h>

#include "Toc.h"
#include "ConnectionWrapper.h"

#define CONTROL_DELETE_BLOCK 2
#define CONTROL_START_BLOCK 3
#define CONTROL_STOP_BLOCK 4
#define CONTROL_RESET 5
#define CONTROL_CREATE_BLOCK_V2 6
#define CONTROL_APPEND_BLOCK_V2 7

#define CONTROL_CH 1
#define CRTP_PORT_LOG 0x05
#define MAX_LEN_NAME 31
#define MAX_LOG_BLOCK_SIZE 26
#define GENERIC_LOG_ERROR 0xFF
#define LOG_SUCCESS 0
struct LogBlock
{
    uint8_t _id;
    std::list<TocItem> _logItems;
    bool _isActive;
};

enum class OccupiedStatus
{
    OCCUPIED,
    NOT_OCCUPIED,
    UNKNOWN
};
class Log
{
private:
    Toc *_tocPtr;
    ConnectionWrapper _conWpr;
    OccupiedStatus idsOccupied[UINT8_MAX] = {OccupiedStatus::UNKNOWN};

public:
    Log(Toc &toc, ConnectionWorker &con);
    ~Log();

    /**
     * If successful returns non-negative integer representing the new logBlock id. eg: id = 5 or id = 0
     * If failed returns the error code as a negative integer. eg: -ENOENT = -2 
    */
    int createLogBlock(uint8_t logType, uint16_t logId);

    /**
     * If successful returns non-negative integer representing the new logBlock id. eg: id = 5 or id = 0
     * If failed returns the error code as a negative integer. eg: -ENOENT = -2 
    */
    int createLogBlock(uint8_t id, uint8_t logType, uint16_t logId);

    /**
     * If successful returns non-negative integer representing the appended logBlock id. eg: id = 5 or id = 0
     * If failed returns the error code as a negative integer. eg: -ENOENT = -2 
    */
    int appendLogBlock(uint8_t id,uint8_t logType, uint16_t logId);

    /**
     * If successful returns non-negative integer representing the deleted logBlock id. eg: id = 5 or id = 0
     * If failed returns the error code as a negative integer. eg: -ENOENT = -2 
    */
    int deleteLogBlock(uint8_t id);

    /**
     * If successful returns non-negative integer representing the logBlock id that was started. eg: id = 5 or id = 0
     * If failed returns the error code as a negative integer. eg: -ENOENT = -2 
    */
    int startLogBlock(uint8_t id, uint8_t period);

    /**
     * If successful returns non-negative integer representing the logBlock id which was stopped. eg: id = 5 or id = 0
     * If failed returns the error code as a negative integer. eg: -ENOENT = -2 
    */
    int stopLogBlock(uint8_t id);

    /**
     * If successful returns 0
     * If failed returns the error code as a negative integer. eg: -ENOENT = -2 
    */
    int resetLogBlocks();
};
