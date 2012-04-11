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
    if ( !isEmpty() ) {
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

bool Buffer::isEmpty()
{
    return _buffer.empty();
}

// By George this method is ugly.
void Buffer::displayBuffer()
{
    queue<int> tempBuffer;

    cout << "[ ";
    //for (unsigned int i = 0; i < _buffer.size(); i++) {
    while (!_buffer.empty()) {
        tempBuffer.push(_buffer.front());
        _buffer.pop();
        cout << tempBuffer.back() << " ";
    }

    while (!tempBuffer.empty()) {
        _buffer.push(tempBuffer.front());
        tempBuffer.pop();
    }

    cout << " ]\n";
    cout << flush;
}
