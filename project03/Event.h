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
    Event(int type, long startTime, int pID);
    ~Event();

    long getStartTime();
    int getType();
    int getPID();

    bool operator< (const Event &param) const;

    //void setStartTime(long startTime);
    //void setType(int type);
    //void setPID(int pID);

private:
    int _type;
    long _startTime;
    int _pID;
};

#endif /* end of include guard: EVENT_H */
