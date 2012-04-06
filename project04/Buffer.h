#ifndef BUFFER_H
#define BUFFER_H

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

    private:
        queue<int> _buffer;
        //int _bufferFront;
        //int _bufferRear;
        unsigned int _maxSize;
};

#endif /* end of include guard: BUFFER_H */
