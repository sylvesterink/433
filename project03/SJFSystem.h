#ifndef SJFSYSTEM_H
#define SJFSYSTEM_H

#include "System.h"

/**
 * @brief The declaration of the SJF system.  Implemented on top of the
 *        system base, with the ready queue as a priority queue
 */
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
        priority_queue<Process*, vector<Process*>, Process::CompStr > readyQueue;
};

#endif /* end of include guard: SJFSYSTEM_H */
