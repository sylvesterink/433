/*
 * @file Buffer.h
 * @brief Declaration of the shared resource buffer
 * @author Cavan Crawford, Brandon Kasa
 * @version 1.0
 * @dat 2012-04-18
 */
#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <queue>
using namespace std;

/*
 * @brief Creates the shared buffer as a queue which allows an item to be inserted or 
          deleted and the entire buffer to be displayed.
*/
class Buffer
{
    public:
        Buffer(int maxSize = 5); //int bufferSize);
        virtual ~Buffer();

        virtual bool insertItem(int newItem);
        virtual bool removeItem(int &removedItem);
        virtual bool isFull();
        virtual bool isEmpty();
        virtual void displayBuffer();

    private:
        queue<int> _buffer;
        unsigned int _maxSize;
};

#endif /* end of include guard: BUFFER_H */
