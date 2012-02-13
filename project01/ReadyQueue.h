/**
 * @file ReadyQueue.h
 * @brief Declaration of the ReadyQueue object, a simple implementation
 *        of a priority queue.  This queue is a heap, implemented as an array,
 *        with the root of the heap being the smallest item, or highest
 *        priority.
 * @author Cavan Crawford, Brandon Kasa
 * @version 1.0
 * @date 2012-02-12
 */

#ifndef READYQUEUE_H
#define READYQUEUE_H

#include <iostream>

using namespace std;

#include "PCB.h"

/**
 * @brief A simple implementation of a priority queue for the PCB object
 *        This is a heap implemented using an array for performance
 */
class ReadyQueue
{
    public:
        // Constructors and Destructor
        ReadyQueue();
        ReadyQueue(int);
        ~ReadyQueue();

        // Interface methods
        bool insertProc(PCB*);
        PCB removeHighestProc();
        int getSize();
        void displayQueue();
        bool isEmpty();
        void agePriority();

    private:
        // Private methods
        void moveDown(int, int);
        void swap(int, int);

    private:
        // Member variables
        PCB** _queueData;
        int _dataSize;
        int _maxSize;

        // Constant Variables
        static const int DEFAULT_SIZE = 20;
};

#endif /* end of include guard: READYQUEUE_H */
