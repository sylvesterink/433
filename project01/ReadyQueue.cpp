/**
 * @file ReadyQueue.cpp
 * @brief The implementation of the ReadyQueue object
 * @author Cavan Crawford, Brandon Kasa
 * @version 1.0
 * @date 2012-02-12
 */
#include "ReadyQueue.h"

/**
 * @brief The constructor, initializes member variables and creates array
 *        for storing data at the default size
 */
ReadyQueue::ReadyQueue():
    _dataSize(0)
{
    _maxSize = DEFAULT_SIZE;
    _queueData = new PCB*[DEFAULT_SIZE];
}

/**
 * @brief Constructor, initializes member variables and creates array
 *        for storing data at the specified size
 * @param size The specified size of the array
 */
ReadyQueue::ReadyQueue(int size):
    _dataSize(0)
{
    _maxSize = size;
    _queueData = new PCB*[size];
}

/**
 * @brief Destructor, cleans up and deallocates members
 */
ReadyQueue::~ReadyQueue()
{
    if (_queueData != NULL) {
        delete[] _queueData;
    }
}

/**
 * @brief Checks if the queue is empty
 * @return True if the queue is empty
 */
bool ReadyQueue::isEmpty()
{
    if (_dataSize == 0) {
        return true;
    }

    return false;
}

/**
 * @brief Insert an item into its proper location in the queue
 * @param newElement The item to be inserted
 * @return Success or failure of insertion
 */
 //TODO: make it possible to dynamically increase the array size as needed
bool ReadyQueue::insertProc(PCB* newElement)
{
    // If the array is full, can't insert any more
    if (_dataSize + 1 > _maxSize) {
        return false;
    }

    // Set initial insert position and priority for comparison
    int insertPos = _dataSize;
    int elPriority = newElement->priority;

    // Set the state of the item now that it is in the queue
    newElement->state = READY;

    // Place as new heap leaf and increase size of queue
    _queueData[_dataSize] = newElement;
    _dataSize++;

    // Sort the heap. Swap the new item with its parent until it finds its place
    // and the heap is valid.
    int parent = (_dataSize/2) - 1;
    while ( (insertPos != 0) && (elPriority < _queueData[parent]->priority) ) {
        _queueData[insertPos] = _queueData[parent];
        _queueData[parent] = newElement;

        insertPos = parent;
        parent = (insertPos/2) - 1;

        // Don't try to go past root
        if (parent < 0) {
            parent = 0;
        }
    }

    return true;
}

/**
 * @brief Remove the highest priority item from the queue
 * @return The object removed
 */
PCB ReadyQueue::removeHighestProc()
{
    // If the queue is empty, return dummy object.
    // TODO: This could be more robust.
    if (_dataSize == 0) {
        PCB failReturn;
        failReturn.id = 0;
        failReturn.priority = 1;
        failReturn.state = TERMINATED;
        return failReturn;
    }

    // Change the state of the process being removed
    _queueData[0]->state = RUNNING;

    // Set up item to return
    PCB returnProcess = *_queueData[0];

    // Move the last leaf to root of heap to take removed item's place
    _queueData[0] = _queueData[_dataSize - 1];

    // Set the last leaf to null, since it is now empty, and decrease size
    _queueData[_dataSize - 1] = NULL;
    _dataSize--;

    // Move the new root down to its appropriate location
    moveDown(0, _dataSize - 1);

    return returnProcess;
}

/**
 * @brief After removing an item from the heap, the heap must be rebuilt.
 *        With the last leaf placed as the new root, it must be swapped down
 *        to its correct location
 * @param firstElement The root of the heap.  (Non-zero is for subheaps)
 * @param lastElement The last leaf in the heap
 */
void ReadyQueue::moveDown(int firstElement, int lastElement)
{
    // Find out if the root has a smaller child and swap with it,
    // then move on to test the subtree with that child as the root
    int smallest = 2 * firstElement + 1;
    // Make sure it doesn't go beyond last element in the array
    while (smallest <= lastElement) {
        // Check which child node is smaller, and choose that
        if ( (smallest < lastElement) &&
                (_queueData[smallest]->priority >
                 _queueData[smallest + 1]->priority) ) {
            smallest++;
        }

        // If the child node is smaller than the current root, swap them
        if (_queueData[firstElement]->priority >
                _queueData[smallest]->priority) {
            swap(firstElement, smallest);

            // Make the child node the new root, and start looking at its
            // children
            firstElement = smallest;
            smallest = 2 * firstElement + 1;
        }
        else {
            // Once the item is in its correct location, set smallest beyond
            // the end of the array so that while loop exits
            smallest = lastElement + 1;
        }
    }
}

/**
 * @brief Swap two locations in the heap (as implemented by an array)
 * @param first First item to swap
 * @param last Second item to swap
 */
void ReadyQueue::swap(int first, int last)
{
    PCB* swapElement = _queueData[first];
    _queueData[first] = _queueData[last];
    _queueData[last] = swapElement;
}

/**
 * @brief Increase the priority of all items in the queue.
 *        Used to prevent an item from sitting in the queue untouched.
 */
void ReadyQueue::agePriority()
{
    // Iterate through each item and increase the priority, with the lower
    // number being the higher priority
    for (int i = 0; i < _dataSize; i++) {
        if (_queueData[i]->priority > 1) {
            _queueData[i]->priority--;
        }
    }
}

/**
 * @brief Get the current size of the queue
 * @return Size of the queue
 */
int ReadyQueue::getSize()
{
    return _dataSize;
}

/**
 * @brief print the current queue contents to std out
 *        Displayed only as a simple array.
 */
void ReadyQueue::displayQueue()
{
    for (int i = 0; i < _dataSize; i++) {
        cout << _queueData[i]->id << " ";
    }

    cout << endl;
}
