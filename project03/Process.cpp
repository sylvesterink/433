#include "Process.h"

Process::Process(int pID, int priority)
{
    _pID = pID;
    _startTime = setStartTime(300000);//0 - 5min
    _priority = priority;
    _totalCpuDuration = setTotalCpuDuration(1000, 60000);//1s - 1min
    _remainingCpuDuration = _totalCpuDuration;
    _avgCpuBurstLength = setAvgCpuBurstLength(5, 100);//5ms - 100ms
    _nextCpuBurstLength = 0; //call provided function in random.cpp
    _ioBurstTime = 0;
    _status = P_WAITING;

}

Process::~Process()
{

}

int Process::getPID()
{
    return _pID;
}

long Process::getStartTime()
{
    return _startTime;
}

long Process::getTotalCpuDuration()
{
    return _totalCpuDuration;
}

long Process::getRemainingCpuDuration()
{
    return _remainingCpuDuration;
}

long Process::getAvgCpuBurstLength()
{
    return _avgCpuBurstLength;
}

long Process::getNextCpuBurstLength()
{
    return _nextCpuBurstLength;
}

long Process::getIoBurstTime()
{
    return _ioBurstTime;
}

int Process::getPriority()
{
    return _priority;
}

int Process::getStatus()
{
    return _status;
}

//Setters
void Process::addTotalCpuDuration(long cpuDurationIncrease)
{
    _totalCpuDuration += cpuDurationIncrease;
}

void Process::setRemainingCpuDuration(long newDuration)
{
    _remainingCpuDuration = newDuration;
}

void Process::setAvgCpuBurstLength(long newAvgLength)
{
    _avgCpuBurstLength = newAvgLength;
}

void Process::setNextCpuBurstLength(long newNextLength)
{
    _nextCpuBurstLength = newNextLength;
}

void Process::setIoBurstTime(long newBurstTime)
{
    _ioBurstTime = newBurstTime;
}

void Process::setStatus(int newStatus)
{
    _status = newStatus;
}

void Process::setNextCpuBurstLength()
{
    _nextCpuBurstLength = CPUBurstRandom(_avgCpuBurstLength); 
}

void Process::setNextIoBurstTime(long minTime, long maxTime)
{
    //30 - 100 ms

    //_nextioBurstTime = something
}

long Process::setStartTime(long maxTime)
{
    //0 - 300,000 ms
    long rand = 0;

    return rand;
}

long Process::setTotalCpuDuration(long minTime, long maxTime)
{
    long rand = 0;

    return rand;
}

long Process::setAvgCpuBurstLength(long minTime, long maxTime)
{
    //5ms - 100ms
    long rand = 0;

    return rand;
}

/* Multiple < needed depending on algorithym used.
   Process::operator<(const Process &param) const
   {
// Implemented using > so that priority is reversed
return (_priority > param._priority);
}
*/
