#include "Event.h"

Event::Event()
{
    //fail.
}

Event::Event(int type, long startTime, int pID)
{
    _type = type;
    _startTime = startTime;
    _pID = pID;
}

Event::~Event()
{

}

long Event::getStartTime()
{
    return _startTime;
}

int Event::getType()
{
    return _type;
}

int Event::getPID()
{
    return _pID;
}

bool Event::operator<(const Event &param) const
{
    // Implemented using > so that priority is reversed
    return (_startTime > param._startTime);
}

//void Event::setStartTime(long startTime)
//{

//}

//void Event::setType(int type)
//{

//}

//void Event::setPID(int pID)
//{

//}
