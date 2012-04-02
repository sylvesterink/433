/**
 * @file Process.cpp
 * @brief Implements the process object
 * @author Cavan Crawford & Brandon Kasa
 * @version 1.0
 * @date 2012-04-02
 */
#include "Process.h"

/**
 * @brief Creates and initializes process
 * @param pID The unique process id
 * @param priority The process priority, used in comparisons
 */
//TODO: Remove hardcoded values and pass by parameter
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

/**
 * @brief Destructor
 */
Process::~Process()
{

}

/**
 * @brief Returns the process id
 * @return The process id
 */
int Process::getPID()
{
    return _pID;
}

/**
 * @brief Returns the process start time
 * @return The process start time
 */
long Process::getStartTime()
{
    return _startTime;
}

/**
 * @brief Gets the amount of time required on cpu
 * @return Time required on cpu
 */
long Process::getTotalCpuDuration()
{
    return _totalCpuDuration;
}

/**
 * @brief Gets the amount of cpu time remaining
 * @return Cpu time remaining
 */
long Process::getRemainingCpuDuration()
{
    return _remainingCpuDuration;
}

/**
 * @brief Gets the average cpu burst length for entire process
 * @return The average Cpu burst length
 */
long Process::getAvgCpuBurstLength()
{
    return _avgCpuBurstLength;
}

/**
 * @brief Gets the next required cpu burst length
 * @return The next required cpu burst length
 */
long Process::getNextCpuBurstLength()
{
    return _nextCpuBurstLength;
}

/**
 * @brief Gets the io burst time required
 * @return The IO burst time
 */
long Process::getIoBurstTime()
{
    return _ioBurstTime;
}

/**
 * @brief Gets the process priority
 * @return Process priority
 */
int Process::getPriority()
{
    return _priority;
}

/**
 * @brief Gets the process state
 * @return The process state
 */
int Process::getStatus()
{
    return _status;
}

//Setters
/**
 * @brief Increases total cpu duration by variable amount
 * @param cpuDurationIncrease Amount to add to cpu duration
 */
void Process::addTotalCpuDuration(long cpuDurationIncrease)
{
    _totalCpuDuration += cpuDurationIncrease;
}

/**
 * @brief Set the remaining cpu duration to specific amount
 * @param newDuration New cpu duration
 */
void Process::setRemainingCpuDuration(long newDuration)
{
    _remainingCpuDuration = newDuration;
}

/**
 * @brief Set the avg cpu burst length
 * @param newAvgLength New cpu burst length
 */
void Process::setAvgCpuBurstLength(long newAvgLength)
{
    _avgCpuBurstLength = newAvgLength;
}

/**
 * @brief Set IO burst time to a random amount
 */
//TODO: This should not be hardcoded
void Process::setIoBurstTime()
{
    _ioBurstTime = rand() % 100 + 30;
}

/**
 * @brief Sets the process state
 * @param newStatus State to set
 */
void Process::setStatus(int newStatus)
{
    _status = newStatus;
}

/**
 * @brief Set the new cpu burst lenght to a random value
 */
void Process::setNextCpuBurstLength()
{
    _nextCpuBurstLength = CPUBurstRandom(_avgCpuBurstLength);
}

/**
 * @brief Set the value from the cpu duration
 * @param newDuration The value to set
 */
void Process::setRemainingCpuBurstLength(long newDuration)
{
    _nextCpuBurstLength = newDuration;
}
//void Process::setNextIoBurstTime(long minTime, long maxTime)
//{
    ////30 - 100 ms

    ////_nextioBurstTime = something
//}

/**
 * @brief Set start time to random value
 * @param maxTime Maximum of randomized value
 */
void Process::randomizeStartTime(long maxTime)
{
    _startTime = rand() % maxTime;
}

/**
 * @brief Set cpu duration to a random value
 * @param minTime Minimum random value
 * @param maxTime Maximum random value
 */
void Process::randomizeTotalCpuDuration(long minTime, long maxTime)
{
    _totalCpuDuration = rand() % maxTime + minTime;
}

/**
 * @brief Set cpu burst length to a random value
 * @param minTime Minimum random value
 * @param maxTime Maximum random value
 */
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

/**
 * @brief Get the time the process completed execution
 * @return Completed time
 */
long Process::getCompletedTime()
{
    return _completedTime;
}

/**
 * @brief Get the amount of time the process spent on CPU
 * @return Service time
 */
long Process::getServiceTime()
{
    return _serviceTime;
}

/**
 * @brief Get the amount of time process spent in IO
 * @return IO time
 */
long Process::getIoTime()
{
    return _ioTime;
}

/**
 * @brief Get the amount of time process was waiting
 * @return Waiting time
 */
long Process::getWaitingTime()
{
    return _waitingTime;
}

/**
 * @brief Set completed time value
 * @param completedTime New completed time
 */
void Process::setCompletedTime(long completedTime)
{
    _completedTime = completedTime;
}

/**
 * @brief Set service time value
 * @param serviceTime New service time
 */
void Process::setServiceTime(long serviceTime)
{
    _serviceTime = serviceTime;
}

/**
 * @brief Set IO time value
 * @param ioTime New io time
 */
void Process::setIoTime(long ioTime)
{
    _ioTime = ioTime;
}

/**
 * @brief Set waiting time value
 * @param waitingTime New waiting time
 */
void Process::setWaitingTime(long waitingTime)
{
    _waitingTime = waitingTime;
}
