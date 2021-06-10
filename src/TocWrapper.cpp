#include "TocWrapper.h"

TocWrapper::TocWrapper(Toc& toc) : WrapperTemplate<Toc, TocWrapper>(toc)
{
}

TocWrapper::~TocWrapper()
{
}

// TocWrapper TocWrapper::WrapperTemplate::operator=(Toc& toc) 