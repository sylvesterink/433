#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <queue>
using namespace std;

static const int BUFFER_SIZE = 5;

class Buffer
{
    public:
        Buffer(); //int bufferSize);
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
