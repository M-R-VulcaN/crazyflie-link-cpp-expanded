#pragma once

#include "WrapperTemplate.h"
#include "Toc.h"

class TocWrapper : WrapperTemplate<Toc, TocWrapper>
{
private:
    /* data */
public:
    TocWrapper(Toc &toc);
    virtual TocWrapper &operator=(Toc &toc)
    {
        WrapperTemplate<Toc, TocWrapper>::_core = &toc;
        return *this;
    }

    //  TocWrapper& WrapperTemplate<Toc, TocWrapper>::operator=(Toc& toc);
    virtual ~TocWrapper();
};
