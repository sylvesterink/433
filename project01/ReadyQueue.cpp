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

void ReadyQueue::insertProc(PCB* newElement)
{
    int insertPos = _dataSize;
    int elPriority = newElement->getPriority();

    _queueData[_dataSize] = newElement;
    _dataSize++;

    int parent = (_dataSize/2) - 1;
    while ( (insertPos != 0) && (elPriority < _queueData[parent]->getPriority()) ) {
        _queueData[insertPos] = _queueData[parent];
        _queueData[parent] = newElement;

        insertPos = parent;
        parent = (insertPos/2) - 1;

        if (parent < 0) {
            parent = 0;
        }
    }

}

PCB ReadyQueue::removeHighestProc()
{
    PCB returnProcess;

    return returnProcess;
}

int ReadyQueue::getSize()
{

    return 0;
}

void ReadyQueue::displayQueue()
{
    for (int i = 0; i < _dataSize; i++) {
        cout << _queueData[i]->getId() << " ";
    }

    cout << endl;
}
