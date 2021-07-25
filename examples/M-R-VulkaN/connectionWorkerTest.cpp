#include "ConnectionWorker.h"
#include <chrono>
#include <iostream>
using bitcraze::crazyflieLinkCpp::Connection;

int main()
{
    Connection con("usb://0");
    ConnectionWorker conWorker(con);
    conWorker.start();
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "end" << std::endl;
    conWorker.stop();
    // // conWorker.stop();
    return 0;
}