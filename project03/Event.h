#ifndef EVENT_H
#define EVENT_H

enum {
    E_PROCESS_ARRIVAL,
    E_CPU_BURST_COMPLETION,
    E_IO_COMPLETION,
    E_TIMER_EXPIRATION
};

class Event
{
public:
    Event();
    ~Event();

private:
    int type;
    long startTime;
    int pID;
};



#endif /* end of include guard: EVENT_H */
