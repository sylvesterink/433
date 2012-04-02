/**
 * @file Event.cpp
 * @brief Implementation of the Event object
 * @author Cavan Crawford & Brandon Kasa
 * @version 1.0
 * @date 2012-04-02
 */
#include "Event.h"

/**
 * @brief Constructor
 */
// TODO: Remove this.  Constructor needs parameters.
Event::Event()
{

}

/**
 * @brief Cretae an event based on the required parameters
 * @param type Type of event
 * @param startTime Time that the event will occur
 * @param pID ID of the process event will affect
 */
Event::Event(int type, long startTime, int pID)
{
    _type = type;
    _startTime = startTime;
    _pID = pID;
}

/**
 * @brief Event destructor
 */
Event::~Event()
{

}

/**
 * @brief Get the start time of the event
 * @return The start time of the event
 */
long Event::getStartTime()
{
    return _startTime;
}

/**
 * @brief Get the event type
 * @return The type of the event
 */
int Event::getType()
{
    return _type;
}

/**
 * @brief Get the program id
 * @return The id of the program the event affects
 */
int Event::getPID()
{
    return _pID;
}

/**
 * @brief Comparator implementation, overloaded for use inn a priority queue
 * @param param The event object to compare with
 * @return Whether this object is greater or less than the other
 */
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
