#include "Crazyflie.h"

int main()
{
    Crazyflie cf("usb://0");
    cf.init();
    int res = cf.createLogBlock({
                                    {"stabilizer", "roll"},
                                    {"oa", "up"},
                                    {"oa", "front"},
                                    {"stabilizer","pitch"},
                                },
                                "test");

    if (res < 0)
        std::cout << "creation Error: " << res << std::endl;
    res = cf.startLogBlock(10, "test");
    if (res < 0)
        std::cout << "starting Error: " << res << std::endl;
    res = cf.createLogBlock({
                                    {"stabilizer", "yaw"},
                                    {"stabilizer","roll"},
                                },
                                "test2");

    if (res < 0)
        std::cout << "creation Error: " << res << std::endl;
    res = cf.startLogBlock(10, "test2");
    if (res < 0)
        std::cout << "starting Error: " << res << std::endl;

    std::mutex mu;
    std::unique_lock<std::mutex> lock(mu);
    std::mutex *muPtr = &mu;
    std::condition_variable waitTillFinished;
    std::condition_variable *waitTillFinishedPtr = &waitTillFinished;
    std::atomic<bool> isFinished(false);
    std::atomic<bool> *isFinishedPtr = &isFinished;
    std::atomic<bool> isCallbackFinished(false);
    std::atomic<bool> *isCallbackFinishedPtr = &isCallbackFinished;
    std::cout << "pass " << res << std::endl;
    cf.addLogCallback([ isFinishedPtr, muPtr, waitTillFinishedPtr, isCallbackFinishedPtr]
    (const std::map<TocItem,void*>& _tocItemsAndValues, uint32_t period)
                      {
                        
                        //   std::lock_guard<std::mutex> lock(*muPtr);
                        //   std::list<TocItem> logBlockItems = log.getLogBlock(id);
                        //   int currDataIndex = 0;
                          std::cout <<"  period:  " << period << "  val=  ";

                            for(auto element : _tocItemsAndValues)
                            {
                            //     // std::cout << std::endl<<to_string(tocItem._type) << std::endl;
                            //   TocItemType type = tocItem._type;
                            //   if ("uint8_t" == type)
                            //   {
                            //       std::cout << (int)data[currDataIndex];
                            //       currDataIndex += sizeof(uint8_t);
                            //   }
                            //   else if ("uint16_t" == type)
                            //   {
                            //       std::cout << *(uint16_t *)(data.data() + currDataIndex);
                            //       currDataIndex += sizeof(uint16_t);
                            //   }
                            //   else if ("uint32_t" == type)
                            //   {
                            //       std::cout << *(uint32_t *)(data.data() + currDataIndex);
                            //       currDataIndex += sizeof(uint32_t);
                            //   }
                            //   else if ("uint64_t" == type)
                            //   {
                            //       std::cout << *(uint64_t *)(data.data() + currDataIndex);
                            //       currDataIndex += sizeof(uint64_t);
                            //   }
                            //   else if ("int8_t" == type)
                            //   {
                            //       std::cout << *(int8_t *)(data.data() + currDataIndex);
                            //       currDataIndex += sizeof(int8_t);
                            //   }
                            //   else if ("int16_t" == type)
                            //   {
                            //       std::cout << *(int16_t *)(data.data() + currDataIndex);
                            //       currDataIndex += sizeof(int16_t);
                            //   }
                            //   else if ("int32_t" == type)
                            //   {
                            //       std::cout << *(int32_t *)(data.data() + currDataIndex);
                            //       currDataIndex += sizeof(int32_t);
                            //   }
                            //   else if ("int64_t" == type)
                            //   {
                            //       std::cout << *(int64_t *)(data.data() + currDataIndex);
                            //       currDataIndex += sizeof(int64_t);
                            //   }
                            //   else if ("FP16" == type)
                            //   {
                            //       std::cout << *(float *)(data.data() + currDataIndex);
                            //       currDataIndex += sizeof(float);
                            //   }
                            //   else if ("float" == type)
                            //   {
                            //       std::cout << *(float *)(data.data() + currDataIndex);
                            //       currDataIndex += sizeof(float);
                            //   }
                            //   else if ("double" == type)
                            //   {
                            //       std::cout << *(float *)(data.data() + currDataIndex);
                            //       currDataIndex += sizeof(float);
                            //   }

                            if(to_string(element.first._type).find("uint")!=std::string::npos)
                            {
                                uint32_t res = 0;
                                std::memcpy(&res, element.second,element.first._type.size());
                                std::cout << res;
                            }
                            else if (to_string(element.first._type).find("int")!=std::string::npos)
                            {
                                int32_t res = 0;
                                std::memcpy(&res, element.second,element.first._type.size());
                                std::cout << res;
                            }
                            else if (element.first._type == "float")
                            {
                                std::cout << *(float*)element.second;
                            }
                             std::cout <<"  ";

                          }
                          std::cout << std::endl;

                          if ((bool)*isFinishedPtr)
                          {
                              *isCallbackFinishedPtr = true;
                              waitTillFinishedPtr->notify_all();
                              return false;
                          }
                          return true;
                      },"test");
                      
    std::cout << "Press enter to stop receiving" << std::endl;
    lock.unlock();
    std::cin.getline(nullptr, 0, '\n');
    lock.lock();
    isFinished = true;
    waitTillFinished.wait(lock, [isCallbackFinishedPtr]()
                          { return (bool)*isCallbackFinishedPtr; });
    return 0;
}