#ifndef RRSYSTEM_H
#define RRSYSTEM_H

#include "System.h"

class RRSystem : public System
{
    public:
        RRSystem();
        virtual ~RRSystem();

        virtual void onProcArrival(Event &event);
        virtual void onCpuComplete(Event &event);
        virtual void onIoComplete(Event &event);
        virtual void dispatch(Event &event);
        virtual void onTimerExpiration(Event &event);

    protected:
        queue<Process*> readyQueue;
};

#endif /* end of include guard: RRSYSTEM_H */
