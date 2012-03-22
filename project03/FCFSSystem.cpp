#include "FCFSSystem.h"

FCFSSystem::FCFSSystem()
{
    CPU = NULL;
}

FCFSSystem::~FCFSSystem()
{
    cleanupProcesses();
}


void FCFSSystem::onProcArrival(Event &event)
{
    cout << "Process Arrived " << event.getPID() << endl;

    readyQueue.push(processList[event.getPID()]);
    dispatch(event);
}

void FCFSSystem::onCpuComplete(Event &event)
{
    cout << "Burst Complete " << event.getPID() << endl;

    Process* currentProcess = CPU;
    CPU = NULL;

    currentProcess->setRemainingCpuDuration(
            currentProcess->getRemainingCpuDuration()
            - currentProcess->getNextCpuBurstLength() );
    if (currentProcess->getRemainingCpuDuration() < 1) {
        currentProcess->setStatus(P_TERMINATED);
        cout << "Process Terminated " << event.getPID() << endl;
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
}

void FCFSSystem::onIoComplete(Event &event)
{
    cout << "IO Complete " << event.getPID() << endl;

    Process* nextProcess = processList[event.getPID()];
    nextProcess->setStatus(P_READY);
    readyQueue.push(nextProcess);
    dispatch(event);
}

void FCFSSystem::dispatch(Event &event)
{
    if (CPU == NULL) {
        Process* nextProcess = readyQueue.front();
        readyQueue.pop();
        CPU = nextProcess;

        CPU->setNextCpuBurstLength();

        long eventStartTime;
        if (CPU->getNextCpuBurstLength() > CPU->getRemainingCpuDuration()) {
            eventStartTime = CPU->getRemainingCpuDuration()
                              + event.getStartTime();
        }
        else {
            eventStartTime = CPU->getNextCpuBurstLength()
                              + event.getStartTime();
        }

        Event newCpuEvent(E_CPU_BURST_COMPLETION, eventStartTime,
                CPU->getPID());

        eventQueue.push(newCpuEvent);
    }
}

