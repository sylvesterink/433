#include "Page.h"

Page::Page() :
    _valid(false),
    _dirty(false),
    _memLocation(0)
{

}

Page::~Page()
{

}

bool Page::isValid()
{
    return _valid;
}

void Page::setDirtyBit(bool setValue)
{
    _dirty = setValue;
}

bool Page::getDirtyBit()
{
    return _dirty;
}

void Page::setValidBit(bool setValue)
{
    _valid = setValue;
}
