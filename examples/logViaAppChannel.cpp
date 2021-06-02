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

int main()
{
    Crazyflie crazyflie("usb://0");

    crazyflie.init();

    crazyflie.setParamByName("usd", "logging", 0, 1);
    crazyflie.setParamByName("usd", "sendAppChannle", 1, 1);

    std::vector<uint8_t> result;
    uint32_t currMemAddress = 0;
    uint32_t dataSize = 0;
    std::ofstream outputFile("log.txt");
    auto start = std::chrono::steady_clock::now();

    do
    {
        result = crazyflie.recvAppChannelData();
        uint8_t packetCode = result[0];
        std::cout << "packet code: " << (int)packetCode << std::endl;
        std::vector<uint8_t> response;
        response.resize(6);
        unsigned int ackRequestMemAddress = 0;

        switch (packetCode)
        {
        case 0:
            std::copy_n(result.begin() + 1, sizeof(dataSize), (uint8_t *)&dataSize);
            std::cout << "Data size: " << dataSize << std::endl;
            response[0] = 0;
            crazyflie.sendAppChannelData(&response[0], sizeof(uint8_t)); //size msg ack
            break;

        case 1:
            std::copy_n(result.begin() + 1, sizeof(currMemAddress), (uint8_t *)&currMemAddress);
            currMemAddress += result.size() - sizeof(currMemAddress) - sizeof(uint8_t);
            std::cout << "Current Memory Address: " << (unsigned int)currMemAddress << std::endl;
            outputFile.write(reinterpret_cast<char *>(&result[5]), result.size() - 5);

            break;

        case 2:
            std::copy_n(result.begin() + 1, sizeof(ackRequestMemAddress), (uint8_t *)&ackRequestMemAddress);

            std::cout << "Ack Request Mem Address: " << ackRequestMemAddress << std::endl;
            if (ackRequestMemAddress == currMemAddress)
            {
                response[0] = 0;
            }
            else
            {
                response[0] = 2;
            }
            std::copy_n((uint8_t *)&currMemAddress, sizeof(currMemAddress), response.begin() + 1);
            std::cout << currMemAddress << std::endl;
            crazyflie.sendAppChannelData(response.data(), sizeof(uint8_t) + sizeof(uint32_t)); //data msg ack
            break;

        default:
            std::cout << "Incorrect Msg type" << currMemAddress << std::endl;
            response[0] = 1;
            crazyflie.sendAppChannelData(response.data(), sizeof(uint8_t));

            break;
        }

    } while (currMemAddress < dataSize);
    outputFile.close();

    std::chrono::duration<double> delta =  std::chrono::steady_clock::now() - start;
    std::cout << "Time [sec]: " << delta.count() << std::endl;
    std::cout << "rate[bytes/sec] : " << dataSize/(delta.count()) <<std::endl;
    return 0;
}