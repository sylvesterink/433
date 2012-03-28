#ifndef SJFSYSTEM_H
#define SJFSYSTEM_H

#include "System.h"

class SJFSystem : public System
{
    public:
        SJFSystem();
        virtual ~SJFSystem();

        virtual void onProcArrival(Event &event);
        virtual void onCpuComplete(Event &event);
        virtual void onIoComplete(Event &event);
        virtual void dispatch(Event &event);

    protected:
        //stackoverflow.com/questions/986021
        priority_queue<Process*> readyQueue;
};

#endif /* end of include guard: SJFSYSTEM_H */
