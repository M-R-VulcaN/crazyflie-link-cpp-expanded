#include "Crazyflie.h"
#include "Log.h"

using namespace bitcraze::crazyflieLinkCpp;

// #define LOG_PORT 5
// // Channels used for the logging port
// #define CHAN_TOC 0
// #define CHAN_SETTINGS 1
// #define CHAN_LOGDATA 2

// // Commands used when accessing the Table of Contents
// #define CMD_TOC_ELEMENT 0  // original version: up to 255 entries
// #define CMD_TOC_INFO 1    // original version: up to 255 entries
// #define CMD_GET_ITEM_V2 2  // version 2: up to 16k entries
// #define CMD_GET_INFO_V2 3  // version 2: up to 16k entries

// // Commands used when accessing the Log configurations
// #define CMD_CREATE_BLOCK 0
// #define CMD_APPEND_BLOCK 1
// #define CMD_DELETE_BLOCK 2
// #define CMD_START_LOGGING 3
// #define CMD_STOP_LOGGING 4
// #define CMD_RESET_LOGGING 5
// #define CMD_CREATE_BLOCK_V2 6
// #define CMD_APPEND_BLOCK_V2 7

int main()
{
    Crazyflie crazyflie("usb://0");
    
    // crazyflie.init();

    // // crazyflie.printLogToc();
    // // crazyflie.printParamToc();

    // std::cout << "Enter log group and name in the following format:(group.name): " << std::endl;
    // std::cin.ignore(INT32_MAX, '\n');
    // uint8_t data[MAX_LEN_NAME] = {0};
    // char userInputStr[MAX_LEN_NAME];
    // userInputStr[MAX_LEN_NAME] = 0;

    // std::cin.getline(userInputStr, MAX_LEN_NAME - 1, '\n');

    // std::string temp = std::string(userInputStr);
    // std::string groupName = temp.substr(0, temp.find("."));
    // std::string paramName = temp.substr(groupName.length() + 1);

    // uint16_t logId = crazyflie._logToc.getItemId(groupName, paramName);
    // auto logType = crazyflie._logToc.getItem(groupName, paramName);

    // Log.createLogBlock(logType ,logId);

    // Log.createLogBlock();
    // Log::createLogBlock(1);
    ////
    // std::cout << tocWpr->getAllTocItems().size();

    // Crazyflie crazyflie("usb://0");
    // // conWrapper.setPort(LOG_PORT);
    // // conWrapper.setChannel(CHAN_TOC);
    // // uint8_t i = CMD_GET_INFO_V2;
    // // conWrapper.sendData(&i,1);
    // // std::cout << conWrappedr.recvFilteredData(0) << std::endl;
    // crazyflie.init();
    //  crazyflie.printLogToc();

    return 0;
}