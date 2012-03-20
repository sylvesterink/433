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

        void addTotalCpuDuration(long cpuDurationIncrease);
        void setRemainingCpuDuration(long newDuration);
        void setAvgCpuBurstLength(long newAvgLength);
        void setNextCpuBurstLength(long newNextLength);
        void setIoBurstTime(long newBurstTime);
        void setStatus(int newStatus);

        void setNextCpuBurstLength();//uses provided functions in random.cpp
        void setNextIoBurstTime(long minTime, long maxTime);

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

        void randomizeStartTime(long maxTime);
        void randomizeTotalCpuDuration(long minTime, long maxTime);
        void randomizeAvgCpuBurstLength(long minTime, long maxTime);

};

#endif /* end of include guard: PROCESS_H */
