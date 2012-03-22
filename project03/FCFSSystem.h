#ifndef FCFSSYSTEM_H
#define FCFSSYSTEM_H

//TODO: REMOVE ME
#include <iostream>

#include "System.h"

class FCFSSystem : public System
{
    public:
        FCFSSystem();
        virtual ~FCFSSystem();

        virtual void onProcArrival(int PID);
        virtual void onCpuComplete(int PID);
        virtual void onIoComplete(int PID);
        virtual void onTimerExpiration(int PID);
        virtual void dispatch();
    protected:
        virtual void cleanupProcesses();

    protected:
        queue<Process*> readyQueue;
};

#endif /* end of include guard: FCFSSYSTEM_H */
