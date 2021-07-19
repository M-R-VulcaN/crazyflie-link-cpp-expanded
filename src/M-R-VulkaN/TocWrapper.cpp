#include "TocWrapper.h"

using bitcraze::crazyflieLinkCpp::Connection;

TocWrapper::TocWrapper(Toc& toc, ConnectionWrapper & conWpr) : WrapperTemplate<Toc, TocWrapper>(toc), _conWpr(&conWpr)
{
}

TocWrapper::~TocWrapper()
{
}


void TocWrapper::initToc() 
{
     // ask for the toc info
    uint8_t cmd = CMD_TOC_INFO_V2;

    _conWpr->sendData(&cmd, sizeof(cmd));

    TocInfo cfTocInfo(_conWpr->recvFilteredData(0));

    uint16_t num_of_elements = cfTocInfo._numberOfElements;

    for (uint16_t i = 0; i < num_of_elements; i++)
    {
        TocItem tocItem();
        _core->insert(getTocItemFromCrazyflie(i));
    }

}

TocItem TocWrapper::getTocItemFromCrazyflie(uint16_t id) const
{
    uint8_t cmd = CMD_TOC_ITEM_V2;
    // ask for a param with the given id
    _conWpr->sendData(&cmd, sizeof(uint8_t), &id, sizeof(id));

    return TocItem(_conWpr->recvFilteredData(0));
}


