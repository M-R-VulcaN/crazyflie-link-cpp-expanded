#include "ConnectionWorker.h"
#include <chrono>
#include <iostream>
using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;

int main()
{
    Connection con("usb://0");
    ConnectionWorker conWorker(con);
    conWorker.start();
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    uint8_t data[] = {1};

    Packet p(data,sizeof(data));
    p.setChannel(0);
    p.setPort(5);
    con.send(p);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    Packet p_recv = conWorker.recvPacket(5,0);
    if(p_recv)
        std::cout << "res: " <<p_recv<< std::endl;
    else
        std::cout << "failed recv" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "end" << std::endl;
    conWorker.stop();
    // // conWorker.stop();
    return 0;
}