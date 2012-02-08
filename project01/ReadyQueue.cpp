#include "ReadyQueue.h"

ReadyQueue::ReadyQueue():
    _dataSize(0),
    _insertPosition(0)
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
        delete[] *_queueData;
    }
}

bool ReadyQueue::isEmpty()
{
    return false;
}

void ReadyQueue::insertProc(PCB* newElement)
{
    _queueData[0] = newElement;
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
    //cout << _queueData[0]->getId() << endl;
}
