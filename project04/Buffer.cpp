/*
 * @file Buffer.cpp
 * @brief Implementation file for the shared resource buffer
 * @author Cavan Crawford and Brandon Kasa
 * @date 2012-04-18
 */
#include "Buffer.h"

/*
 * @brief buffer constructor
 * @param maximum size of the buffer resource
 */
Buffer::Buffer(int maxSize): //int bufferSize):
    _maxSize(maxSize)
{

}

/*
 * @brief buffer destructor
 */
Buffer::~Buffer()
{

}

/*
 * @brief Insert item into buffer.
 * @param Integer item to insert
 * @return Succes or failure if the buffer is full
 */
bool Buffer::insertItem(int newItem)
{
    if (!isFull()) {
        _buffer.push(newItem);

        return true;
    }

    return false;
}

/*
 * @brief remove item from buffer.
 * @param Integer item to set
 * @return Succes or failure if the buffer is empty
 */
bool Buffer::removeItem(int &removedItem)
{
    if ( !isEmpty() ) {
        removedItem = _buffer.front();
        _buffer.pop();

        return true;
    }

    return false;
}

/*
 * @brief Check if the buffer is full
 * @return True if buffer is full, or false
 */
bool Buffer::isFull()
{
    if ( _buffer.size() >= _maxSize ) {
        return true;
    }

    return false;
}

/*
 * @brief Check if buffer is empty
 * @return True if buffer is empty, or false
 */
bool Buffer::isEmpty()
{
    return _buffer.empty();
}

/*
 * @brief Display contents of the buffer using style [ x y z ]
 *        Each element is removed from the buffer, added to a temp buffer, and displayed.
          Each item is then placed back in the original buffer
 */
void Buffer::displayBuffer()
{
    queue<int> tempBuffer;

    cout << "[ ";
    //Move each item to a temporary buffer
    while (!_buffer.empty()) {
        tempBuffer.push(_buffer.front());
        _buffer.pop();
        cout << tempBuffer.back() << " ";
    }

    //Return elements to the original buffer
    while (!tempBuffer.empty()) {
        _buffer.push(tempBuffer.front());
        tempBuffer.pop();
    }

    //Display stream
    cout << "]\n";
    cout << flush;
}
