#ifndef PCB_H
#define PCB_H

enum { NEW, READY, RUNNING, WAITING, TERMINATED };

struct PCB
{
    int id;
    int state;
    int priority;
};

    //public:
        //PCB();
        //~PCB();

        //void setId(int);
        //void setState(int);
        //void setPriority(int);

        //int getId();
        //int getState();
        //int getPriority();

    //private:
        //int _id;
        //int _state;
        //int _priority;
#endif /* end of include guard: PCB_H */
