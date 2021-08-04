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
// #define MAX_LEN_NAME 32

enum UserChoices
{
    EXIT_CHOICE,
    CREATE_BLOCK_CHOICE,
    APPEND_BLOCK_CHOICE,
    DELETE_BLOCK_CHOICE,
    START_BLOCK_CHOICE,
    STOP_BLOCK_CHOICE,
    BLOCK_RESET,
    LOG_RECEIVE
};

int main()
{
    Crazyflie crazyflie("usb://0");
    
    const Toc &tocRef = crazyflie.getLogToc();
    crazyflie.init();
    Log& log = crazyflie._log;
    while (true)
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));
        uint16_t userInput = 0;

        std::cout << "===================================" << std::endl;
        std::cout << "Menu:" << std::endl;
        std::cout << "1 - Create Log Block" << std::endl;
        std::cout << "2 - Append To Log Block" << std::endl;
        std::cout << "3 - Delete Log Block" << std::endl;
        std::cout << "4 - Start receiving from Log Block" << std::endl;
        std::cout << "5 - Stop receiving from Log Block" << std::endl;
        std::cout << "6 - log reset - delete all log blocks" << std::endl;
        std::cout << "7 - log receive - receive the log blocks which are started" << std::endl;
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
                char userInputStr[MAX_LEN_NAME];
                userInputStr[MAX_LEN_NAME] = 0;

                std::cin.getline(userInputStr, MAX_LEN_NAME - 1, '\n');

                std::string temp = std::string(userInputStr);
                std::string groupName = temp.substr(0, temp.find("."));
                std::string paramName = temp.substr(groupName.length() + 1);

                uint16_t logId = tocRef.getItemId(groupName, paramName);
                auto tocItem = tocRef.getItem(groupName, paramName);

                int response = log.createLogBlock(0,tocItem._type._type,logId);

                if(response<0)
                {
                    std::cout << "An Error Occured: "<< -response <<std::endl;
                }
                else
                {
                    std::cout << "Success! Log Block Id = " << response <<std::endl;
                }
            std::cout << "pass" << std::endl;

            }
            break;

        case APPEND_BLOCK_CHOICE:
            std::cin.ignore(INT32_MAX, '\n');
            {
                std::cout << "Enter log block id: " << std::endl;
                int logBlockId = 0;
                std::cin >> logBlockId;
                std::cin.ignore(INT32_MAX, '\n');
                std::cout << "Enter log group and name in the following format:(group.name): " << std::endl;
                char userInputStr[MAX_LEN_NAME];
                userInputStr[MAX_LEN_NAME] = 0;

                std::cin.getline(userInputStr, MAX_LEN_NAME - 1, '\n');

                std::string temp = std::string(userInputStr);
                std::string groupName = temp.substr(0, temp.find("."));
                std::string paramName = temp.substr(groupName.length() + 1);

                uint16_t logId = tocRef.getItemId(groupName, paramName);
                auto tocItem = tocRef.getItem(groupName, paramName);
                int response = log.appendLogBlock(logBlockId,tocItem._type._type,logId);
                if(response<0)
                {
                    std::cout << "An Error Occured: "<< -response<<std::endl;
                }
                else
                {
                    std::cout << "Successfully appended log block!     Log Block Id = " <<response<<std::endl;
                }
            }
            break;

        case DELETE_BLOCK_CHOICE:
            {
                int id = 0; //add a check function if the id exist
                std::cout << "Enter log id:" << std::endl;
                std::cin >> id;
                int response = log.deleteLogBlock(id);
                if(response<0)
                {
                    std::cout << "An Error Occured: "<< -response<<std::endl;
                }
                else
                {
                    std::cout << "Successfully deleted log block!     Log Block Id = " <<response<<std::endl;
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
                if(PeriodTimeInMs/10 > 0)
                {
                    int response = log.startLogBlock(id, PeriodTimeInMs/10);
                    if(response<0)
                    {
                        std::cout << "An Error Occured: "<< -response<<std::endl;
                    }
                    else
                    {
                        std::cout << "Successfully started logging!     Log Block Id = " <<response<<std::endl;
                    }
                    break;
                }
                else
                {   
                    std::cout << "Error! perion time should be more than 10! (in ms)" << std::endl;
                }
                break;    
            }

        case STOP_BLOCK_CHOICE:
            {
                int id = 0; //add a check function if the id exist
                std::cout << "Enter log id:" << std::endl;
                std::cin >> id;
                
                int response = log.stopLogBlock(id);
                if(response<0)
                    {
                        std::cout << "An Error Occured: "<< -response<<std::endl;
                    }
                    else
                    {
                        std::cout << "Successfully Stopped logging!     Log Block Id = " <<response<<std::endl;
                    }
                break;
            }
        case BLOCK_RESET:
            {
                int response = log.resetLogBlocks();
                if(response<0)
                    {
                        std::cout << "An Error Occured: "<< -response<<std::endl;
                    }
                    else
                    {
                        std::cout << "Success! Finished reseting all blocks"<<std::endl;
                    }
                break;
            }
        case LOG_RECEIVE:
{
            std::cin.ignore(INT32_MAX, '\n');

            std::mutex mu;
            std::unique_lock<std::mutex> lock(mu);
            std::mutex *muPtr = &mu;
            std::condition_variable waitTillFinished;
            std::condition_variable *waitTillFinishedPtr = &waitTillFinished;
            std::atomic<bool> isFinished(false);
            std::atomic<bool> *isFinishedPtr = &isFinished;
            std::atomic<bool> isCallbackFinished(false);
            std::atomic<bool> *isCallbackFinishedPtr = &isCallbackFinished;

            crazyflie.addLogCallback([log,isFinishedPtr,muPtr,waitTillFinishedPtr,isCallbackFinishedPtr](uint8_t id, uint32_t period, const std::vector<uint8_t>& data){
                std::lock_guard<std::mutex> lock(*muPtr);
                std::list<TocItem> logBlockItems = log.getLogBlock(id);
                int currDataIndex = 0;
                std::cout << "period: "<<period << " val=";
                for(TocItem tocItem : logBlockItems)
                {
                    TocItemType type = tocItem._type;
                    if ("uint8_t" == type)
                    {
                        std::cout << data[currDataIndex];
                    }
                    else if ("uint16_t" == type)
                    {
                        std::cout << *(uint16_t*)data.data()+currDataIndex;
                    }
                    else if ("uint32_t" == type)
                    {
                        std::cout << *(uint32_t*)data.data()+currDataIndex;
                    }
                    else if ("uint64_t" == type)
                    {
                        std::cout << *(uint64_t*)data.data()+currDataIndex;
                    }
                    else if ("int8_t" == type)
                    {
                        std::cout << *(int8_t*)data.data()+currDataIndex;
                    }
                    else if ("int16_t" == type)
                    {
                        std::cout << *(int16_t*)data.data()+currDataIndex;
                    }
                    else if ("int32_t" == type)
                    {
                        std::cout << *(int32_t*)data.data()+currDataIndex;
                    }
                    else if ("int64_t" == type)
                    {
                        std::cout << *(int64_t*)data.data()+currDataIndex;
                    }
                    else if ("FP16" == type)
                    {
                        std::cout << *(float*)data.data()+currDataIndex;
                    }
                    else if ("float" == type)
                    {
                        std::cout << *(float*)data.data()+currDataIndex;
                    }
                    else if ("double" == type)
                    {
                        std::cout << *(float*)data.data()+currDataIndex;
                    }
                    std::cout <<std::endl;
                }
                if((bool)*isFinishedPtr)
                {
                    *isCallbackFinishedPtr = true;
                    waitTillFinishedPtr->notify_all();
                    return false;
                }
                return true;
            }); 
            std::cout << "Press enter to stop receiving"<<std::endl;
            lock.unlock();
            std::cin.getline(nullptr,0,'\n'); 
            lock.lock(); 
            isFinished = true;
            waitTillFinished.wait(lock,[isCallbackFinishedPtr](){return (bool)*isCallbackFinishedPtr;});       
            break;
        }

        default:
            break;
        }
    }

    return 0;
}
