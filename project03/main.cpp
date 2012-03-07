#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#include "Event.h"

void initializeEventQueue();
void handleEvent();

int main(int argc, const char *argv[])
{
    //priority_queue<Event, vector<Event> > eventQueue;
    //int endTime = 300;
    initializeEventQueue();

    //int currentTime = 0;

    Event one(0,0,0);
    Event two(1,1,1);

    if(two < one)
        cout << "valid" << endl;

    //while ( (!eventQueue.empty()) && (currentTime < endTime) ) {
        ////Event nextEvent = eventQueue.pop();
        ////currentTime = nextEvent.getStartTime();
        //handleEvent();
    //}

    return 0;
}

void initializeEventQueue()
{

}

void handleEvent()
{

}
