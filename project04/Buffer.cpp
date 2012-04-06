#include "Buffer.h"

Buffer::Buffer(): //int bufferSize):
    _maxSize(BUFFER_SIZE)
{

}

Buffer::~Buffer()
{

}

bool Buffer::insertItem(int newItem)
{
    if (!isFull()) {
        _buffer.push(newItem);

        return true;
    }

    return false;
}

bool Buffer::removeItem(int &removedItem)
{
    if ( !_buffer.empty() ) {
        removedItem = _buffer.front();
        _buffer.pop();

        return true;
    }

    return false;
}

bool Buffer::isFull()
{
    if ( _buffer.size() >= _maxSize ) {
        return true;
    }

    return false;
}
