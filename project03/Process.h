#ifndef PROCESS_H
#define PROCESS_H

enum {
    P_READY,
    P_RUNNING,
    P_WAITING,
    P_TERMINATED
};

class Process
{
public:
    Process(int pID, long startTime, int priority);
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

private:
    int _pID;
    long _startTime;
    long _totalCpuDuration;
    long _remainingCpuDuration;
    long _avgCpuBurstLength;
    long _nextCpuBurstLength;
    long _ioBurstTime;
    int _priority;
    int _status;
};



#endif /* end of include guard: PROCESS_H */
