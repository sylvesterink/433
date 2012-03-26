#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

#include "Event.h"
#include "Process.h"

class System {
    public:
        System();
        virtual ~System();

        virtual void initializeProcesses(int numProcesses);
        void simulation(int numProcesses, int maxTime);

        virtual void onProcArrival(Event &event) = 0;
        virtual void onCpuComplete(Event &event) = 0;
        virtual void onIoComplete(Event &event) = 0;
        virtual void dispatch(Event &event) = 0;

        virtual void handleEvent(Event &event);
        virtual void reportStatistics();

    protected:
        virtual void cleanupProcesses();

    protected:
        priority_queue<Event> eventQueue;

        vector<Process*> processList;
        //vector<Process*> IOQueue;

        Process* CPU;
        int _maxTime;
};

#endif /* end of include guard: SYSTEM_H */
