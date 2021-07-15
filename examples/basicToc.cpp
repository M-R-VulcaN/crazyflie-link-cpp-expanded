#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <sstream>
#include <queue>
#include <vector>

#include "Crazyflie.h"

using namespace bitcraze::crazyflieLinkCpp;

int main()
{
    Crazyflie crazyflie("usb://0");
    crazyflie.init();

    crazyflie.printParamToc();


    std::string path = "/home/makeruser/crazyflie-link-cpp-expanded";
    std::string fileName = "toc.csv";

    crazyflie.csvParamToc(path, fileName);

    return 0;
}