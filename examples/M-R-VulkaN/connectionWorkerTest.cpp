#include "ConnectionWorker.h"

using bitcraze::crazyflieLinkCpp::Connection;

int main()
{
    Connection con("usb://0");
    ConnectionWorker conWorker(con);
    conWorker.start();
    // conWorker.stop();
    return 0;
}