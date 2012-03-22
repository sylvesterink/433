#include "System.h"

System::System()
{

}

System::~System()
{

}

void System::initializeProcesses(int numProcesses)
{
    for (int i = 0; i < numProcesses; i++) {
        Process* newProcess = new Process(i);
        processList.push_back(newProcess);

        Event newEvent(E_PROCESS_ARRIVAL, newProcess->getStartTime(), i);
        eventQueue.push(newEvent);
    }

}

//TODO: Move into System object
void System::simulation(int numProcesses, int maxTime)
{
    initializeProcesses(numProcesses);

    int currentTime = 0;

    while ( (!eventQueue.empty()) && (currentTime < maxTime) ) {
        Event nextEvent = eventQueue.top();
        eventQueue.pop();
        currentTime = nextEvent.getStartTime();
        handleEvent(nextEvent);
    }
}

void System::handleEvent(Event &event)
{
    int eventType = event.getType();

    switch (eventType) {
        case E_PROCESS_ARRIVAL:
            onProcArrival(event);
            //handle_proc_arrival(e)
            break;
        case E_CPU_BURST_COMPLETION:
            onCpuComplete(event);
            //handle_CPU_completion(e)
            break;
        case E_IO_COMPLETION:
            onIoComplete(event);
            //handle_IO_completion(e)
            break;
        case E_TIMER_EXPIRATION:
            onTimerExpiration(event);
            //handle_Timer_expiration(e)
            break;
    }

    //schedular.run();
}

void System::cleanupProcesses()
{
    for (unsigned int i = 0; i < processList.size(); i++) {
        if (processList[i] != NULL) {
            delete processList[i];
            processList[i] = NULL;
        }
    }
}
