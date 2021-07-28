#include "ConnectionWorker.h"
#include "Crazyflie.h"
#include <chrono>
#include <iostream>
using bitcraze::crazyflieLinkCpp::Connection;
using bitcraze::crazyflieLinkCpp::Packet;

bool func(const Packet& p_recv)
{

    if(p_recv)
        std::cout << "res1: " <<p_recv.payloadSize()<< std::endl;
    // else
        std::cout << "failed recv1" << std::endl;
        return true;
    
}

bool func2(Packet p_recv)
{
    if(p_recv)
        std::cout << "res2: " <<p_recv<< std::endl;
    else
        std::cout << "failed recv2" << std::endl;
    return true;
}

bool func3(const char* str)
{
    // if(str)
    //     std::cout << "res2: " <<str<< std::endl;
    // else
    //     std::cout << "failed recv2" << std::endl;
    std::cout <<"###" <<str;
    return false;
}

bool func4(const char* str)
{
    // if(str)
    //     std::cout << "res2: " <<str<< std::endl;
    // else
    //     std::cout << "failed recv2" << std::endl;
    std::cout <<str;
    return true;
}

int main()
{
    Connection con("usb://0");
    ConnectionWorker conWorker(con);
    // Crazyflie cf("usb://0");
    // cf.init();
    // cf.addConsoleCallback(func3);
    // cf.addConsoleCallback(func4);

    // cf.addLogCallback( func);
    // conWorker.addCallback({5,0,func});
    // conWorker.addCallback({5,0,func2});

    conWorker.start();
    std::cout <<"recv: " << conWorker.recv(0,0)<< std::endl;
    // // std::this_thread::sleep_for(std::chrono::seconds(10));
    // uint8_t data[] = {1};

    // Packet p(data,sizeof(data));
    // p.setChannel(0);
    // p.setPort(5);
    // con.send(p);
    // con.send(p);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    // Packet p_recv = conWorker.recvPacket(5,0);
    
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << "end" << std::endl;
    // conWorker.stop();
    // // conWorker.stop();
    return 0;
}