#ifndef READYQUEUE_H
#define READYQUEUE_H

struct PCB_t {
    int _id;
    int _state;
    int _priority;
};

class ReadyQueue
{
    public:
        ReadyQueue();
        ~ReadyQueue();

        void insertProc();
        PCB_t removeHighestProc();
        int getSize();
        void displayQueue();

    private:
};


#endif /* end of include guard: READYQUEUE_H */
