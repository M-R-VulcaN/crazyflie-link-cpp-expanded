#include "Crazyflie.h"

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;

#define CONTROL_CREATE_BLOCK_V2 6
#define CONTROL_CH  1
#define CRTP_PORT_LOG  0x05
#define MAX_LEN_NAME  31

enum UserChoices
{
    EXIT_CHOICE,
    CREATE_BLOCK_CHOICE,
    APPEND_BLOCK_CHOICE,
    LIST_BLOCKS_CHOICE,
    DELETE_BLOCK_CHOICE,
    START_BLOCK_CHOICE
};

int main()
{
    bool idsOccupied[UINT8_MAX] = {false};
    Crazyflie crazyflie("usb://0");
    ConnectionWrapper conWpr(crazyflie.getCon());
    conWpr.setChannel(1);
    conWpr.setPort(5);
    crazyflie.init();
    // char userInputStr[MAX_LEN_NAME] = {0};
    // userInputStr[MAX_LEN_NAME-1] = 0;
    
    std::cout << "logger:\n enter the new log id: " << std::endl;
    std::string temp;
    std::string groupName;
    std::string paramName;
    // uint16_t logId = 0;
    // oa.up
    while(true)
    {
        int i =0;
        uint16_t userInput =0;

        std::cout << "Menu:"<<std::endl;
        std::cout << "1 - Create Log Block"<<std::endl;
        std::cout << "2 - Append To Log Block"<<std::endl;
        std::cout << "3 - List Log Blocks"<<std::endl;
        std::cout << "4 - Delete Log Block"<<std::endl;
        std::cout << "5 - Start receiving from Log Block"<<std::endl;
        std::cout << "0 - Exit"<<std::endl;
        std::cout << ">> ";
        std::cin >> userInput;

        switch (userInput)
        {
        case EXIT_CHOICE:
            return 0;
        case CREATE_BLOCK_CHOICE:
            std::cout << "Enter log group and name in the following format:(group.name): "<<std::endl;
            std::cin.ignore(INT32_MAX,'\n');
        {
            uint8_t data[MAX_LEN_NAME] = {0};
            char userInputStr[MAX_LEN_NAME];
            userInputStr[MAX_LEN_NAME] = 0;

            std::cin.getline (userInputStr, MAX_LEN_NAME-1,'\n');

             std::string temp = std::string(userInputStr);
             std::string groupName  = temp.substr(0,temp.find("."));
             std::string paramName = temp.substr(groupName.length()+1);

             uint16_t   logId = crazyflie._logToc.getItemId(groupName,paramName);
             auto tocItem = crazyflie._logToc.getItem(groupName,paramName);
              
            data[0] = CONTROL_CREATE_BLOCK_V2;
            data[1] = 0;
            data[2] =  tocItem._accessType._accessType<<6 | tocItem._type._type ;
            
            data[3] = logId&0xff;
            data[4] =logId>>8;
            uint8_t failCode = 0;

            for(i =0 ;i < UINT8_MAX;i++)
            {
                if(!idsOccupied[i])
                {
                    idsOccupied[i] = true;
                    data[1]=i;
                    conWpr.sendData(data,5);
                    Packet p_recv = conWpr.recvFilteredData(0);
                    failCode=p_recv.payload()[2];
                    if(17==failCode)
                        continue;
                    break;  
                }
            }
            
            if(0 == failCode)
            {
                std::cout << "Success! id = "<<(int) i<<std::endl;
            }
            else
            {
                std::cout << "Failiure! code = " << (int)failCode<<std::endl;
            }
            
        }

            
            break;
        // std::cout << ">> ";


        //     break;
        case APPEND_BLOCK_CHOICE:
            return 0;
        case LIST_BLOCKS_CHOICE:
            return 0;
        case DELETE_BLOCK_CHOICE:
            return 0;
        case START_BLOCK_CHOICE:
            return 0;
        
        default:
            break;
        }
    }
    
    return 0;
}