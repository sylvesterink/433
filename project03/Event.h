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
    Event(int type, long int startTime, int pID);
    ~Event();

    long int getStartTime();
    int getType();
    int getPID();

    bool operator < (Event);

    //void setStartTime(long startTime);
    //void setType(int type);
    //void setPID(int pID);

private:
    int _type;
    long int _startTime;
    int _pID;
};



#endif /* end of include guard: EVENT_H */
