#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

#include "FCFSSystem.h"

static const int MAX_RUNTIME = 300000; // 5 minutes in milliseconds

void handleEvent(Event&, System*);


int main(int argc, const char *argv[])
{
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " [NUMPROCESSES]" << endl;
        return 1;
    }

    int numProcesses = atoi(argv[1]);

    if (numProcesses < 1) {
        cerr << "Too few processes!" << endl;
        return 1;
    }

    cout << "Discrete Event Simulator" << endl;
    cout << "Cavan Crawford and Brandon Kasa" << endl;

    srand( time(NULL) );

    priority_queue<Event> eventQueue;
    FCFSSystem simSystem;
    simSystem.initializeProcesses(numProcesses, eventQueue);

    int currentTime = 0;

    while ( (!eventQueue.empty()) && (currentTime < MAX_RUNTIME) ) {
        Event nextEvent = eventQueue.top();
        eventQueue.pop();
        currentTime = nextEvent.getStartTime();
        handleEvent(nextEvent, &simSystem);
    }

    return 0;
}

//TODO: Move into System object
void handleEvent(Event &e, System* simSystem)
{
    simSystem->handleEvent(e);
    //int eventType = e.getType();

    //switch (eventType) {
        //case E_PROCESS_ARRIVAL:
            //simSystem->onProcArrival(e.getPID());
            ////handle_proc_arrival(e)
            //break;
        //case E_CPU_BURST_COMPLETION:
            //simSystem->onCpuComplete(e.getPID());
            ////handle_CPU_completion(e)
            //break;
        //case E_IO_COMPLETION:
            //simSystem->onIoComplete(e.getPID());
            ////handle_IO_completion(e)
            //break;
        //case E_TIMER_EXPIRATION:
            //simSystem->onTimerExpiration(e.getPID());
            ////handle_Timer_expiration(e)
            //break;
    //}

    //schedular.run();
}
