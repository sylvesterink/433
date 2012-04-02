/**
 * @file SJFSystem.cpp
 * @brief The implementation of the Shortest Job First scheduler
 *        The only difference between this and FCFS is that the ready queue is
 *        implemented as a priority queue, meaning the ordering of the
 *        processes is now based on burst length.
 * @author Cavan Crawford & Brandon Kasa
 * @version 1.0
 * @date 2012-04-02
 */
#include "SJFSystem.h"

/**
 * @brief Constructor
 */
SJFSystem::SJFSystem()
{
    CPU = NULL;
}

/**
 * @brief Destructor
 */
SJFSystem::~SJFSystem()
{

}

/**
 * @brief Simulates the arrival of a process to the program
 *        Adds process to the ready queue and dispatches the first process
 * @param event The event specifying the process arrival
 */
void SJFSystem::onProcArrival(Event &event)
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
void SJFSystem::onCpuComplete(Event &event)
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
        currentProcess->setIoBurstTime();
        //TODO: Add statistics here
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
void SJFSystem::onIoComplete(Event &event)
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
 * @brief Simulate the dispatch of the process to the cpu.
 *        If the CPU is free, put the next ready process on it
 * @param event The current event
 */
void SJFSystem::dispatch(Event &event)
{
    // Make sure the CPU is free and there are processes ready, then add to cpu
    if ( (CPU == NULL) && (!readyQueue.empty()) ) {
        Process* nextProcess = readyQueue.top();
        readyQueue.pop();
        CPU = nextProcess;

        // set the burst length of the process
        CPU->setNextCpuBurstLength();

        // Make sure the event will be of appropriate length and keep track of
        // process statistics
        long eventStartTime;
        if (CPU->getNextCpuBurstLength() > CPU->getRemainingCpuDuration()) {
            eventStartTime = CPU->getRemainingCpuDuration()
                              + event.getStartTime();
            nextProcess->setServiceTime(nextProcess->getServiceTime()
                                + nextProcess->getRemainingCpuDuration());
        }
        else {
            eventStartTime = CPU->getNextCpuBurstLength()
                              + event.getStartTime();
            nextProcess->setServiceTime(nextProcess->getServiceTime()
                                + nextProcess->getNextCpuBurstLength());
        }

        // Add the new event to the event queue
        Event newCpuEvent(E_CPU_BURST_COMPLETION, eventStartTime,
                CPU->getPID());

        eventQueue.push(newCpuEvent);
    }
}

