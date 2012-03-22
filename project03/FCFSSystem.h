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

        virtual void onProcArrival(Event &event);
        virtual void onCpuComplete(Event &event);
        virtual void onIoComplete(Event &event);
        virtual void dispatch(Event &event);

    protected:
        queue<Process*> readyQueue;
};

#endif /* end of include guard: FCFSSYSTEM_H */
