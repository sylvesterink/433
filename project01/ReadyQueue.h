#ifndef READYQUEUE_H
#define READYQUEUE_H

#include <iostream>

using namespace std;

#include "PCB.h"

class ReadyQueue
{
    public:
        ReadyQueue();
        //ReadyQueue(int);
        ~ReadyQueue();

        void insertProc(PCB*);
        PCB removeHighestProc();
        int getSize();
        void displayQueue();
        bool isEmpty();

    private:
        void moveDown(int, int);
        void swap(int, int);

    private:
        PCB** _queueData;
        int _dataSize;
};


#endif /* end of include guard: READYQUEUE_H */
