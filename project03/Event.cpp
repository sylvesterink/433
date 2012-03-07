#include "Event.h"

Event::Event()
{
    //fail.
}

Event::Event(int type, long int startTime, int pID)
{
    _type = type;
    _startTime = startTime;
    _pID = pID;
}

Event::~Event()
{

}

long int Event::getStartTime()
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

bool Event::operator<(Event param)
{
    return (_startTime < param.getStartTime());
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
