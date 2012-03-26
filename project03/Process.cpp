#include "Process.h"

Process::Process(int pID, int priority)
{
    _pID = pID;
    _priority = priority;

    randomizeStartTime(300000);//0 - 5min
    randomizeTotalCpuDuration(1000, 60000);//1s - 1min
    randomizeAvgCpuBurstLength(5, 100);//5ms - 100ms

    _remainingCpuDuration = _totalCpuDuration;
    _nextCpuBurstLength = 0; //call provided function in random.cpp
    _ioBurstTime = 0;
    _status = P_READY;

    _completedTime = 0;
    _serviceTime = 0;
    _ioTime = 0;
    _waitingTime = 0;
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

void Process::setIoBurstTime()
{
    _ioBurstTime = rand() % 100 + 30;
}

void Process::setStatus(int newStatus)
{
    _status = newStatus;
}

void Process::setNextCpuBurstLength()
{
    _nextCpuBurstLength = CPUBurstRandom(_avgCpuBurstLength);
}

//void Process::setNextIoBurstTime(long minTime, long maxTime)
//{
    ////30 - 100 ms

    ////_nextioBurstTime = something
//}

void Process::randomizeStartTime(long maxTime)
{
    _startTime = rand() % maxTime;
}

void Process::randomizeTotalCpuDuration(long minTime, long maxTime)
{
    _totalCpuDuration = rand() % maxTime + minTime;
}

void Process::randomizeAvgCpuBurstLength(long minTime, long maxTime)
{
    _avgCpuBurstLength = rand() % maxTime + minTime;
}

/* Multiple < needed depending on algorithym used.
   Process::operator<(const Process &param) const
   {
// Implemented using > so that priority is reversed
return (_priority > param._priority);
}
*/

long Process::getCompletedTime()
{
    return _completedTime;
}

long Process::getServiceTime()
{
    return _serviceTime;
}

long Process::getIoTime()
{
    return _ioTime;
}

long Process::getWaitingTime()
{
    return _waitingTime;
}

void Process::setCompletedTime(long completedTime)
{
    _completedTime = completedTime;
}

void Process::setServiceTime(long serviceTime)
{
    _serviceTime = serviceTime;
}

void Process::setIoTime(long ioTime)
{
    _ioTime = ioTime;
}

void Process::setWaitingTime(long waitingTime)
{
    _waitingTime = waitingTime;
}

