#ifndef READYQUEUE_H
#define READYQUEUE_H

#include <iostream>

using namespace std;

#include "PCB.h"

class ReadyQueue
{
    public:
        ReadyQueue();
        ~ReadyQueue();

        void insertProc();
        PCB removeHighestProc();
        int getSize();
        void displayQueue();
	bool isEmpty();

    private:
};


#endif /* end of include guard: READYQUEUE_H */
