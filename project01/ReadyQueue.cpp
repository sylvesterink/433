#include "ReadyQueue.h"

ReadyQueue::ReadyQueue():
    _dataSize(0)
{
    _queueData = new PCB*[20];
}

//ReadyQueue::ReadyQueue(int size)
//{
    //_queueData = new PCB*[20];
//}

ReadyQueue::~ReadyQueue()
{
    if (_queueData != NULL) {
        delete[] _queueData;
    }
}

bool ReadyQueue::isEmpty()
{
    if (_dataSize == 0) {
        return true;
    }

    return false;
}

//TODO: Make sure we aren't adding more than max quantity
void ReadyQueue::insertProc(PCB* newElement)
{
    int insertPos = _dataSize;
    int elPriority = newElement->priority;

    newElement->state = READY;

    _queueData[_dataSize] = newElement;
    _dataSize++;

    int parent = (_dataSize/2) - 1;
    while ( (insertPos != 0) && (elPriority < _queueData[parent]->priority) ) {
        _queueData[insertPos] = _queueData[parent];
        _queueData[parent] = newElement;

        insertPos = parent;
        parent = (insertPos/2) - 1;

        if (parent < 0) {
            parent = 0;
        }
    }

}

//TODO: make sure we aren't removing too many
PCB ReadyQueue::removeHighestProc()
{
    _queueData[0]->state = RUNNING;

    PCB returnProcess = *_queueData[0];

    _queueData[0] = _queueData[_dataSize - 1];

    _queueData[_dataSize - 1] = NULL;
    _dataSize--;

    moveDown(0, _dataSize - 1);

    return returnProcess;
}

void ReadyQueue::moveDown(int firstElement, int lastElement)
{
    int smallest = 2 * firstElement + 1;
    while (smallest <= lastElement) {
        if ( (smallest < lastElement) &&
                (_queueData[smallest]->priority >
                 _queueData[smallest + 1]->priority) ) {
            smallest++;
        }

        if (_queueData[firstElement]->priority >
                _queueData[smallest]->priority) {
            swap(firstElement, smallest);

            firstElement = smallest;
            smallest = 2 * firstElement + 1;
        }
        else {
            smallest = lastElement + 1;
        }
    }
}

void ReadyQueue::swap(int first, int last)
{
    PCB* swapElement = _queueData[first];
    _queueData[first] = _queueData[last];
    _queueData[last] = swapElement;
}

void ReadyQueue::agePriority()
{
    for (int i = 0; i < _dataSize; i++) {
        if (_queueData[i]->priority > 1) {
            _queueData[i]->priority--;
        }
    }
}

int ReadyQueue::getSize()
{
    return _dataSize;
}

void ReadyQueue::displayQueue()
{
    for (int i = 0; i < _dataSize; i++) {
        cout << _queueData[i]->id << "|";
        cout << _queueData[i]->priority << " ";
    }

    cout << endl;
}
