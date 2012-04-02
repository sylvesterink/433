#ifndef PROCESS_H
#define PROCESS_H

#include <cstdlib>
#include <ctime>
#include "random.h"

enum {
    P_READY,
    P_RUNNING,
    P_WAITING,
    P_TERMINATED
};

class Process
{
    public:
        Process(int pID, int priority=0);
        ~Process();

        int getPID();
        long getStartTime();
        long getTotalCpuDuration();
        long getRemainingCpuDuration();
        long getAvgCpuBurstLength();
        long getNextCpuBurstLength();
        long getIoBurstTime();
        int getPriority();
        int getStatus();

        long getCompletedTime();
        long getServiceTime();
        long getIoTime();
        long getWaitingTime();

        void addTotalCpuDuration(long cpuDurationIncrease);
        void setRemainingCpuDuration(long newDuration);
        void setAvgCpuBurstLength(long newAvgLength);
        void setIoBurstTime();
        void setStatus(int newStatus);

        void setCompletedTime(long completedTime);
        void setServiceTime(long serviceTime);
        void setIoTime(long ioTime);
        void setWaitingTime(long waitingTime);

        void setNextCpuBurstLength();//uses provided functions in random.cpp
	void setRemainingCpuBurstLength(long newDuration);
        //void setNextIoBurstTime(long minTime, long maxTime);

        //bool operator< (const Process &param) const;

        struct CompStr {
            bool operator()(Process* m1, Process* m2) {return m1->_remainingCpuDuration > m2->_remainingCpuDuration;}

        };

    private:
        int _pID;
        long _startTime;
        long _totalCpuDuration;
        long _remainingCpuDuration;
        long _avgCpuBurstLength;
        int _nextCpuBurstLength;
        long _ioBurstTime;
        int _priority;
        int _status;

        long _completedTime;
        long _serviceTime;
        long _ioTime;
        long _waitingTime;

        void randomizeStartTime(long maxTime);
        void randomizeTotalCpuDuration(long minTime, long maxTime);
        void randomizeAvgCpuBurstLength(long minTime, long maxTime);
};


#endif /* end of include guard: PROCESS_H */
