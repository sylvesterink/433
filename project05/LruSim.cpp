#include "LruSim.h"

LruSim::LruSim(int pageSize, int memSize, int logMemSize) :
    Simulator(pageSize, memSize, logMemSize)
{

}

LruSim::~LruSim()
{

}

void LruSim::replacePage(int pageIndex, bool isWrite)
{
    int repLocation = _useOrder.front();
    _useOrder.pop_front();

    _pageFaults++;

    //cout << "Replacing " << repLocation << " with " << pageIndex << endl;
    if (_pageTable[repLocation].getDirtyBit()) {
        _numFlushes++;
    }
    _pageTable[repLocation].setValidBit(false);
    _pageTable[repLocation].setDirtyBit(false);

    _pageTable[pageIndex].setDirtyBit(isWrite);
    _pageTable[pageIndex].setValidBit(true);

    _useOrder.push_back(pageIndex);
}

void LruSim::accessPage(int pageIndex, bool writeBit)
{
    Simulator::accessPage(pageIndex, writeBit);

    list<int>::iterator pos;

    pos = find(_useOrder.begin(), _useOrder.end(), pageIndex);
    _useOrder.erase(pos);
    _useOrder.push_back(pageIndex);
}

void LruSim::insertPage(int pageIndex, bool writeBit)
{
    Simulator::insertPage(pageIndex, writeBit);

    _useOrder.push_back(pageIndex);
}
