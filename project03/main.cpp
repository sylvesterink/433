#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#include "Event.h"
#include "Process.h"

void initializeEventQueue();
void initializeProcesses();
void handleEvent();


int main(int argc, const char *argv[])
{
    priority_queue<Event> eventQueue;
    queue<Process> pQueue;
    int endTime = 300;
    initializeEventQueue();

    int currentTime = 0;

    while ( (!eventQueue.empty()) && (currentTime < endTime) ) {
        Event nextEvent = eventQueue.top();
        eventQueue.pop();
        currentTime = nextEvent.getStartTime();
        handleEvent();
    }

    return 0;
}

void initializeEventQueue()
{

}

void handleEvent()
{

}
