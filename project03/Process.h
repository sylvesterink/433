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
    Process();
    ~Process();

private:
    int pID;
    long startTime;
    long totalCpuDuration;
    long remainingCpuDuration;
    long avgCpuBurstLength;
    long nextCpuBurstLength;
    long ioBurstTime;
    int priority;
    int status;
};



#endif /* end of include guard: PROCESS_H */
