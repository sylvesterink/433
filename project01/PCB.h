#ifndef PCB_H
#define PCB_H

enum { NEW, READY, RUNNING, WAITING, TERMINATED };

struct PCB
{
    int id;
    int state;
    int priority;
};

#endif /* end of include guard: PCB_H */
