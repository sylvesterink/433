#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <queue>

using namespace std;

#include "Event.h"
#include "Process.h"

class System {
    public:
        System();
        virtual ~System();

        virtual void initializeProcesses(int numProcesses,
                priority_queue<Event>& eventQueue);
        virtual void onProcArrival(int PID) = 0;
        virtual void onCpuComplete(int PID) = 0;
        virtual void onIoComplete(int PID) = 0;
        virtual void onTimerExpiration(int PID) = 0;
        virtual void dispatch() = 0;

        void handleEvent(Event &e);

    protected:
        virtual void cleanupProcesses() = 0;

    protected:
        vector<Process*> processList;
        vector<Process*> IOQueue;

        Process* CPU;
};

#endif /* end of include guard: SYSTEM_H */
