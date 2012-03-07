#include "Process.h"

Process::Process(int pID, long startTime, int priority)
{
  _pID = pID;
  _startTime = startTime;
  _priority = priority;
  _totalCpuDuration = 0;
  _remainingCpuDuration = 0;
  _avgCpuBurstLength = 0;
  _nextCpuBurstLength = 0; //Add function here
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

/* Multiple < needed depending on algorithym used.
Process::operator<(const Process &param) const
{
    // Implemented using > so that priority is reversed
    return (_priority > param._priority);
}
*/
