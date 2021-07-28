#include <algorithm>
#include <chrono>
#include <errno.h>
#include "Crazyflie.h"

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;

// #define CONTROL_APPEND_BLOCK    1
#define CONTROL_DELETE_BLOCK 2
#define CONTROL_START_BLOCK 3
#define CONTROL_STOP_BLOCK 4
#define CONTROL_RESET 5
#define CONTROL_CREATE_BLOCK_V2 6
#define CONTROL_APPEND_BLOCK_V2 7


#define CONTROL_CH 1
#define CRTP_PORT_LOG 0x05
#define MAX_LEN_NAME 32

Packet globalPacket;
enum UserChoices
{
    EXIT_CHOICE,
    CREATE_BLOCK_CHOICE,
    APPEND_BLOCK_CHOICE,
    DELETE_BLOCK_CHOICE,
    START_BLOCK_CHOICE,
    STOP_BLOCK_CHOICE,
    BLOCK_RESET
};

Packet getPacket()
{
    while(!globalPacket)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    Packet res = globalPacket;
    globalPacket = Packet();
    return res;
}

int main()
{
    bool idsOccupied[UINT8_MAX] = {false};
    Crazyflie crazyflie("usb://0");
    ConnectionWrapper conWpr(crazyflie._conWorker);
    const Toc& tocRef = crazyflie.getLogToc();
    conWpr.setChannel(1);
    conWpr.setPort(5);
    crazyflie.init();
    crazyflie._conWorker.addCallback({5,1,[](Packet p_recv){globalPacket = p_recv; return true;}});

    while (true)
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));
        int i = 0;
        uint16_t userInput = 0;

        std::cout << "===================================" << std::endl;
        std::cout << "Menu:" << std::endl;
        std::cout << "1 - Create Log Block" << std::endl;
        std::cout << "2 - Append To Log Block" << std::endl;
        std::cout << "3 - Delete Log Block" << std::endl;
        std::cout << "4 - Start receiving from Log Block" << std::endl;
        std::cout << "5 - Stop receiving from Log Block" << std::endl;
        std::cout << "6 - log reset - delete all log blocks" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << ">> ";
        std::cin >> userInput;

        switch (userInput)
        {
        case EXIT_CHOICE:
            return 0;
        case CREATE_BLOCK_CHOICE:
            std::cout << "Enter log group and name in the following format:(group.name): " << std::endl;
            std::cin.ignore(INT32_MAX, '\n');
            {
                uint8_t data[MAX_LEN_NAME] = {0};
                char userInputStr[MAX_LEN_NAME];
                userInputStr[MAX_LEN_NAME] = 0;

                std::cin.getline(userInputStr, MAX_LEN_NAME - 1,'\n');

                std::string temp = std::string(userInputStr);
                std::string groupName = temp.substr(0, temp.find("."));
                std::string paramName = temp.substr(groupName.length() + 1);

                uint16_t logId = tocRef.getItemId(groupName, paramName);
                auto tocItem = tocRef.getItem(groupName, paramName);

                data[0] = CONTROL_CREATE_BLOCK_V2;
                data[1] = 0;
                data[2] = tocItem._accessType._accessType << 6 | tocItem._type._type;

                data[3] = logId & 0xff;
                data[4] = logId >> 8;
                uint8_t failCode = 0;

                for (i = 0; i < UINT8_MAX; i++)
                {
                    if (!idsOccupied[i])
                    {
                        idsOccupied[i] = true;
                        data[1] = i;
                        conWpr.sendData(data, 5);
                        Packet p_recv = getPacket();
                        std::cout << p_recv << std::endl;
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
            }

            break;
        // std::cout << ">> ";

        //     break;
        case APPEND_BLOCK_CHOICE:

            std::cin.ignore(INT32_MAX, '\n');
            {
                std::cout << "Enter log block id: " << std::endl;
                int logBlockId = 0;
                std::cin >> logBlockId;
                std::cin.ignore(INT32_MAX, '\n');
                std::cout << "Enter log group and name in the following format:(group.name): " << std::endl;
                uint8_t data[MAX_LEN_NAME] = {0};
                char userInputStr[MAX_LEN_NAME];
                userInputStr[MAX_LEN_NAME] = 0;

                std::cin.getline(userInputStr, MAX_LEN_NAME - 1, '\n');

                std::string temp = std::string(userInputStr);
                std::string groupName = temp.substr(0, temp.find("."));
                std::string paramName = temp.substr(groupName.length() + 1);

                uint16_t logId = tocRef.getItemId(groupName, paramName);
                auto tocItem = tocRef.getItem(groupName, paramName);

                data[0] = CONTROL_APPEND_BLOCK_V2;
                data[1] = logBlockId;
                data[2] = tocItem._accessType._accessType << 6 | tocItem._type._type;

                data[3] = logId & 0xff;
                data[4] = logId >> 8;
                uint8_t failCode = 0;

                conWpr.sendData(data, 5);
                Packet p_recv = getPacket();
                failCode = p_recv.payload()[2];
                if (0 == failCode)
                {
                    std::cout << "Success! id = " << (int)logBlockId << std::endl;
                }
                else
                {
                    std::cout << "Failiure! code = " << (int)failCode << std::endl;
                }
            }
            break;

        case DELETE_BLOCK_CHOICE:
        {
            int id = 0; //add a check function if the id exist
            std::cout << "Enter log id:" << std::endl;
            std::cin >> id;
            uint8_t data[2] = {0};

            data[0] = CONTROL_DELETE_BLOCK; //define : delete block
            data[1] = id;                      //block id

            uint8_t failCode = 0;

            for (i = 0; i < UINT8_MAX; i++)
            {
                if (!idsOccupied[i])
                {
                    idsOccupied[i] = false;
                    // data[1] = i;
                    conWpr.sendData(data, 2);
                    Packet p_recv = getPacket();
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
            break;
        }
        case START_BLOCK_CHOICE:
        {
            int id = 0; //add a check function if the id exist
            int PeriodTimeInMs = 0;
            std::cout << "Enter log id:" << std::endl;
            std::cin >> id;
            std::cout << "Enter perion time in ms:" << std::endl;
            std::cin >> PeriodTimeInMs;
            uint8_t data[3] = {0};

            data[0] = CONTROL_START_BLOCK;
            data[1] = id;
            data[2] = PeriodTimeInMs / 10;        //time in ms / 10 = senti seconds

            uint8_t failCode = 0;

            conWpr.sendData(data, 3);
            Packet p_recv = getPacket();
            failCode = p_recv.payload()[2];
            std::cout << (int)data[2] << std::endl;
            std::cout << p_recv << std::endl;
            // if (17 == failCode)
            //     continue;
            // break;

            if (0 == failCode)
            {
                std::cout << "Success! starting log on id " << (int)data[1] << " period(ms/10): " << PeriodTimeInMs / 10 << std::endl;
            }
            else
            {
                std::cout << "Failiure! code = " << (int)failCode << std::endl;
            }
            break;
        }

        case STOP_BLOCK_CHOICE:
        {
            int id = 0; //add a check function if the id exist
            // int PeriodTimeInMs = 0;
            std::cout << "Enter log id:" << std::endl;
            std::cin >> id;
            uint8_t data[2] = {0};

            data[0] = CONTROL_START_BLOCK;
            data[1] = id;

            uint8_t failCode = 0;

            conWpr.sendData(data, 2);
            Packet p_recv = getPacket();
            failCode = p_recv.payload()[2];
            std::cout << (int)data[2] << std::endl;
            std::cout << p_recv << std::endl;

            if (0 == failCode)
            {
                std::cout << "Success! Stopping log on id " << (int)data[1] << std::endl;
            }
            else
            {
                std::cout << "Failiure! code = " << (int)failCode << std::endl;
            }
            break;
        }
        case BLOCK_RESET:
        {
            uint8_t data[1] = {0};
            data[0] = CONTROL_RESET;

            uint8_t failCode = 0;

            conWpr.sendData(data, 1);
            Packet p_recv = getPacket();
            failCode = p_recv.payload()[2];

            std::fill(idsOccupied, idsOccupied + UINT8_MAX, false);

            if (0 == failCode)
            {
                std::cout << "Success! deleted all blocks" << std::endl;
            }
            else
            {
                std::cout << "Failiure! code = " << (int)failCode << std::endl;
            }
            break;
        }

        default:
            break;
        }
    }

    return 0;
}