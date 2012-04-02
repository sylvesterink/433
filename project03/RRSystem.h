#ifndef RRSYSTEM_H
#define RRSYSTEM_H

#include "System.h"

class RRSystem : public System
{
    public:
        RRSystem(int Q);
	RRSystem();
        virtual ~RRSystem();

        virtual void onProcArrival(Event &event);
        virtual void onCpuComplete(Event &event);
        virtual void onIoComplete(Event &event);
	void onTimerExpiration(Event &event);
        virtual void dispatch(Event &event);

    protected:
        queue<Process*> readyQueue;
	int QUANTUM;
};

#endif /* end of include guard: FCFSSYSTEM_H */
