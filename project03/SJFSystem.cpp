#include "SJFSystem.h"

SJFSystem::SJFSystem()
{
    CPU = NULL;
}

SJFSystem::~SJFSystem()
{

}


void SJFSystem::onProcArrival(Event &event)
{
    readyQueue.push(processList[event.getPID()]);
    dispatch(event);
}

void SJFSystem::onCpuComplete(Event &event)
{
    Process* currentProcess = CPU;
    CPU = NULL;

    currentProcess->setRemainingCpuDuration(
            currentProcess->getRemainingCpuDuration()
            - currentProcess->getNextCpuBurstLength() );

    if (currentProcess->getRemainingCpuDuration() < 1) {
        currentProcess->setStatus(P_TERMINATED);
        currentProcess->setCompletedTime(event.getStartTime());
    }
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
    dispatch(event);
}

void SJFSystem::onIoComplete(Event &event)
{
    Process* nextProcess = processList[event.getPID()];
    nextProcess->setStatus(P_READY);

    nextProcess->setIoTime(nextProcess->getIoTime()
                            + nextProcess->getIoBurstTime());
    readyQueue.push(nextProcess);
    dispatch(event);
}

void SJFSystem::dispatch(Event &event)
{
    if ( (CPU == NULL) && (!readyQueue.empty()) ) {
        Process* nextProcess = readyQueue.front();
        readyQueue.pop();
        CPU = nextProcess;

        CPU->setNextCpuBurstLength();

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

        Event newCpuEvent(E_CPU_BURST_COMPLETION, eventStartTime,
                CPU->getPID());

        eventQueue.push(newCpuEvent);
    }
}

