#include "Crazyflie.h"


int main()
{
    Crazyflie cf("usb://0");
    cf.init();
    int res = cf.createLogBlock({
        {"oa","up"},
        {"oa","front"},
        {"stabilizer","roll"},
        {"stabilizer","pitch"},
    },"test");

    if(res < 0)
        std::cout << "creation Error: "<< res<<std::endl;
    res = cf.startLogBlock(40,"test");
      if(res < 0)
        std::cout << "starting Error: "<< res<<std::endl;
    Log& log = cf._log;


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

            cf.addLogCallback([log,isFinishedPtr,muPtr,waitTillFinishedPtr,isCallbackFinishedPtr](uint8_t id, uint32_t period, const std::vector<uint8_t>& data){
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
    return 0;
}