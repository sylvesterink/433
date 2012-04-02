#include "RRSystem.h"

RRSystem::RRSystem(int Q)
{
    CPU = NULL;
    QUANTUM = Q;
}

RRSystem::RRSystem()
{
    CPU = NULL;
    QUANTUM = 40;
}

RRSystem::~RRSystem()
{

}


void RRSystem::onProcArrival(Event &event)
{
    readyQueue.push(processList[event.getPID()]);
    dispatch(event);
}

void RRSystem::onCpuComplete(Event &event)
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

void RRSystem::onIoComplete(Event &event)
{
    Process* nextProcess = processList[event.getPID()];
    nextProcess->setStatus(P_READY);

    nextProcess->setIoTime(nextProcess->getIoTime()
                            + nextProcess->getIoBurstTime());
    readyQueue.push(nextProcess);
    dispatch(event);
}

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

void RRSystem::dispatch(Event &event)
{
    if ( (CPU == NULL) && (!readyQueue.empty()) ) {
        Process* nextProcess = readyQueue.front();
        readyQueue.pop();
        CPU = nextProcess;

	//Only get a new burst length if the previous has been completed.
	if(CPU->getNextCpuBurstLength() < 1)
	  CPU->setNextCpuBurstLength();

        long eventStartTime;
	if(QUANTUM > CPU->getRemainingCpuDuration() )
	{
	  eventStartTime = CPU->getRemainingCpuDuration() + event.getStartTime();
	  nextProcess->setServiceTime(nextProcess->getServiceTime()
				      + nextProcess->getRemainingCpuDuration());

	  Event newCpuEvent(E_CPU_BURST_COMPLETION, eventStartTime, CPU->getPID());
          eventQueue.push(newCpuEvent);

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

