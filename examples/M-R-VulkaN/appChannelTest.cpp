#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <sstream>
#include <queue>
#include <vector>
#include <thread>
#include "Crazyflie.h"

using namespace bitcraze::crazyflieLinkCpp;
bool appChannelCallback(const uint8_t *data, uint8_t dataLen)
{
    for (int i = 0; i < dataLen; i++)
    {
        std::cout << (int)data[i] << " ";
    }
    std::cout << std::endl;
    return true;
}
int main()
{
    Crazyflie crazyflie("usb://0");

    crazyflie.init();

    crazyflie.setParamByName("usd", "logging", 0);
    crazyflie.setParamByName("usd", "sendAppChannle", 1);

    // std::vector<uint8_t> res;
    crazyflie.addAppChannelCallback(appChannelCallback);
    int i = 0;
    std::cin >> i;
    // do
    // {
    //     // res = crazyflie.recvAppChannelData();

    //     uint16_t sendData = 0;
    //     crazyflie.sendAppChannelData(&sendData, sizeof(sendData));

    //     for (auto element : res)
    //     {
    //         std::cout << (int)element;
    //     }
    //     std::cout << std::endl;

    // } while (res.size() > 0);

    return 0;
}