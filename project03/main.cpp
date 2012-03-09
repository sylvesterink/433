#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

#include "Event.h"
#include "Process.h"

static const int MAX_RUNTIME = 300000; // 5 minutes in milliseconds

void initializeProcesses(vector<Process*>&, int);
void initializeEventQueue();
void handleEvent(Event&);

void cleanupProcesses(vector<Process*>&);


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

    cout << numProcesses << endl;
    priority_queue<Event> eventQueue;

    vector<Process*> processList;
    queue<Process*> pQueue;

    initializeProcesses(processList, numProcesses);
    initializeEventQueue();


    //TODO: Remove, for testing only
    for (unsigned int i = 0; i < processList.size(); i++) {
        cout << processList.at(i)->getPID() << " " << processList.at(i)->getStartTime() << endl;
    }


    int currentTime = 0;

    while ( (!eventQueue.empty()) && (currentTime < MAX_RUNTIME) ) {
        Event nextEvent = eventQueue.top();
        eventQueue.pop();
        currentTime = nextEvent.getStartTime();
        handleEvent(nextEvent);
    }

    return 0;
}

//TODO: Memory Leak In Here!  Run valgrind to check
void initializeProcesses(vector<Process*>& processList, int numProcesses)
{
    for (int i = 0; i < numProcesses; i++) {
        Process* newProcess = new Process(i);
        processList.push_back(newProcess);
    }

}

void initializeEventQueue()
{

}

void handleEvent(Event &e)
{
    int eventType = e.getType();

    switch (eventType) {
        case E_PROCESS_ARRIVAL:
            //handle_proc_arrival(e)
            break;
        case E_CPU_BURST_COMPLETION:
            //handle_CPU_completion(e)
            break;
        case E_IO_COMPLETION:
            //handle_IO_completion(e)
            break;
        case E_TIMER_EXPIRATION:
            //handle_Timer_expiration(e)
            break;
    }

    //schedular.run();
}

void cleanupProcesses(vector<Process*>& processList)
{
    for (unsigned int i = 0; i < processList.size(); i++) {
        delete processList[i];
    }

}
