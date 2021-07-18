#include "ConnectionWrapper.h"

using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;

#define CONTROL_CREATE_BLOCK_V2 6
#define CONTROL_CH  1
#define CRTP_PORT_LOG  0x05

Packet recvFilteredData(int timeout, int port, int channel, Connection* conPtr)
{
    while (true)
    {
        Packet p = conPtr->recv(timeout);
        if ((p.channel() == channel && p.port() == port) || !p)
            return p;
    }
}

int main()
{
    int newBlockID = 0;
    Connection con("usb://0");
    ConnectionWrapper conWpr(con);

    std::cout << "logger:\n enter the new log id: " << std::endl;
    std::cin >> newBlockID;
    //create a new log
    conWpr.setPort(5);                    //port 5
    conWpr.setChannel(CONTROL_CH);        //channel 1 (Log control: Used for adding/removing/starting/pausing log blocks)
    int idOfFirstLogVariable = 32;        //?
    //int newBlockID = 30;                  //the id i chose for the new block that i create

    conWpr.sendData(&newBlockID, sizeof(newBlockID), &idOfFirstLogVariable, sizeof(idOfFirstLogVariable));
    std::cout << conWpr.recvFilteredData(0) << std::endl;





    // Packet p;
    // p.payload()[0] = CONTROL_CREATE_BLOCK_V2; // 6
    // p.payload()[1] = 11;                      // 11
    // p.payload()[2] = 25;                      // 25
    // p.setPort(CRTP_PORT_LOG);                 // 0x05
    // p.setChannel(CONTROL_CH);                 // 1
    // p.setPayloadSize(3);                      // 3
    
    // con.send(p);

    // Packet p_recv = recvFilteredData(0, CRTP_PORT_LOG, CONTROL_CH, &con);

    // std::cout << p_recv << std::endl;
    // Packet(channel=1,port=5,safelinkUp=1,safelinkDown=1,data=6 11 0 ,seq=43)
    
    return 0;
}