#include "Param.h"


// float Param::getFloatFromCrazyflie(uint16_t paramId) const
// {
//     float res = 0;

//     _conWrapperParamRead.sendData(&paramId, sizeof(paramId));
//     Packet p = _conWrapperParamRead.recvFilteredData(0);
//     std::memcpy(&res, p.payload() + PAYLOAD_VALUE_BEGINING_INDEX, sizeof(res));

//     return res;
// }

// uint32_t Param::getUIntFromCrazyflie(uint16_t paramId) const
// {
//     uint32_t res = 0;
//     _conWrapperParamRead.sendData(&paramId, sizeof(paramId));

//     Packet p = _conWrapperParamRead.recvFilteredData(0);

//     std::memcpy(&res, p.payload() + PAYLOAD_VALUE_BEGINING_INDEX, p.payloadSize() - PAYLOAD_VALUE_BEGINING_INDEX);

//     return res;
// }
