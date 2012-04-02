#include "RRSystem.h"

/**
 * @brief Constructor
 * @param Q The quantum value
 */
RRSystem::RRSystem(int Q)
{
    CPU = NULL;
    QUANTUM = Q;
}

/**
 * @brief Default constructor
 */
RRSystem::RRSystem()
{
    CPU = NULL;
    QUANTUM = 40;
}

/**
 * @brief Destructor
 */
RRSystem::~RRSystem()
{

}

/**
 * @brief Simulates the arrival of a process to the program
 *        Adds process to the ready queue and dispatches the first process
 * @param event The event specifying the process arrival
 */
void RRSystem::onProcArrival(Event &event)
{
    readyQueue.push(processList[event.getPID()]);
    dispatch(event);
}

/**
 * @brief Simulates the completion of a process on the cpu
 *        When the CPU burst completes, the process is placed into the IO queue
 *        if it is incomplete, otherwise the process is terminated
 * @param event The event specifying CPU completion
 */
void RRSystem::onCpuComplete(Event &event)
{
    Process* currentProcess = CPU;
    CPU = NULL;

    // Subtract the amount of time the process spent on the cpu from its
    // remaining time requirement
    currentProcess->setRemainingCpuDuration(
            currentProcess->getRemainingCpuDuration()
            - currentProcess->getNextCpuBurstLength() );

    // If no time remains, the process is complete, so terminate
    if (currentProcess->getRemainingCpuDuration() < 1) {
        currentProcess->setStatus(P_TERMINATED);
        currentProcess->setCompletedTime(event.getStartTime());
    }
    // Otherwise send it to the IO queue
    else {
        currentProcess->setNextCpuBurstLength();
        currentProcess->setIoBurstTime();

        currentProcess->setStatus(P_WAITING);

        long eventStartTime = event.getStartTime()
            + currentProcess->getIoBurstTime();
        Event newIoEvent(E_IO_COMPLETION, eventStartTime,
                currentProcess->getPID());

        eventQueue.push(newIoEvent);
    }
    // Dispatch the next ready event
    dispatch(event);
}

/**
 * @brief Simulate the completion of the processes IO burst
 * @param event The event signifying the end of the IO burst
 */
void RRSystem::onIoComplete(Event &event)
{
    // Move the process back to the ready queue
    Process* nextProcess = processList[event.getPID()];
    nextProcess->setStatus(P_READY);

    // Keep track of how much time the process has spent in IO queue
    nextProcess->setIoTime(nextProcess->getIoTime()
            + nextProcess->getIoBurstTime());
    readyQueue.push(nextProcess);

    // If the next process is ready, dispach it
    dispatch(event);
}

/**
 * @brief Handle the expiration of the quantum assigned to the process
 * @param event The event to handle
 */
void RRSystem::onTimerExpiration(Event &event)
{
    Process* currentProcess = CPU;
    CPU = NULL;

    currentProcess->setRemainingCpuDuration(
            currentProcess->getRemainingCpuDuration() - QUANTUM );

    if (currentProcess->getRemainingCpuDuration() < 1) {
        currentProcess->setStatus(P_TERMINATED);
        currentProcess->setCompletedTime(event.getStartTime());
    }
    else {

        currentProcess->setRemainingCpuBurstLength(
                long(currentProcess->getNextCpuBurstLength() - QUANTUM));

        if(currentProcess->getNextCpuBurstLength() < 1) {

            currentProcess->setIoBurstTime();
            currentProcess->setStatus(P_WAITING);

            long eventStartTime = event.getStartTime()
                + currentProcess->getIoBurstTime();
            Event newIoEvent(E_IO_COMPLETION, eventStartTime,
                    currentProcess->getPID());

            eventQueue.push(newIoEvent);
        }
        else {
            readyQueue.push(currentProcess);
        }
    }
    dispatch(event);

}

/**
 * @brief Simulate the dispatch of the process to the cpu.
 *        If the CPU is free, put the next ready process on it
 * @param event The current event
 * @NOTE Cavan is responsible for this code that needs desperately to be
 *       refactored.  However, he managed to figure this out at the last
 *       minute, so props to him.
 */
//TODO: Clean up this code
void RRSystem::dispatch(Event &event)
{
    // Make sure the CPU is free and there are processes ready, then add to cpu
    if ( (CPU == NULL) && (!readyQueue.empty()) ) {
        Process* nextProcess = readyQueue.front();
        readyQueue.pop();
        CPU = nextProcess;

        // Make sure the event will be of appropriate length and keep track of
        // process statistics
        long eventStartTime;
        if(QUANTUM > CPU->getRemainingCpuDuration() )
        {
            if ( CPU->getRemainingCpuDuration() < CPU->getNextCpuBurstLength() ) {
                eventStartTime = CPU->getRemainingCpuDuration() + event.getStartTime();
                nextProcess->setServiceTime(nextProcess->getServiceTime()
                        + nextProcess->getRemainingCpuDuration());

                Event newCpuEvent(E_CPU_BURST_COMPLETION, eventStartTime, CPU->getPID());
                eventQueue.push(newCpuEvent);
            }
            else {
                eventStartTime = CPU->getNextCpuBurstLength() + event.getStartTime();
                nextProcess->setServiceTime(nextProcess->getServiceTime()
                        + nextProcess->getNextCpuBurstLength());

                Event newCpuEvent(E_CPU_BURST_COMPLETION, eventStartTime, CPU->getPID());
                eventQueue.push(newCpuEvent);
            }
        }
        else
        {
            if(QUANTUM > CPU->getNextCpuBurstLength())
            {
                eventStartTime = CPU->getNextCpuBurstLength() + event.getStartTime();
                nextProcess->setServiceTime(nextProcess->getServiceTime()
                        + nextProcess->getNextCpuBurstLength());

                Event newCpuEvent(E_CPU_BURST_COMPLETION, eventStartTime, CPU->getPID());
                eventQueue.push(newCpuEvent);

            }
            else
            {
                eventStartTime = event.getStartTime() + QUANTUM;
                nextProcess->setServiceTime(nextProcess->getServiceTime() + QUANTUM);

                Event newCpuEvent(E_TIMER_EXPIRATION, eventStartTime, CPU->getPID());
                eventQueue.push(newCpuEvent);

            }
        }
    }
}

