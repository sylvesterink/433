#include "FIFOsim.h"

FIFOsim::FIFOsim(int pageSize, int memSize, int logMemSize) :
    Simulator(pageSize, memSize, logMemSize)
{

}

FIFOsim::~FIFOsim()
{

}

void FIFOsim::replacePage(int pageIndex, bool isWrite)
{
    int repLocation = pageOrder.front();
    pageOrder.pop();

    _pageFaults++;

    //cout << "Replacing " << repLocation << " with " << pageIndex << endl;
    if (_pageTable[repLocation].getDirtyBit()) {
        _numFlushes++;
    }
    _pageTable[repLocation].setValidBit(false);
    _pageTable[repLocation].setDirtyBit(false);

    _pageTable[pageIndex].setDirtyBit(isWrite);
    _pageTable[pageIndex].setValidBit(true);

    pageOrder.push(pageIndex);
}

void FIFOsim::insertPage(int pageIndex, bool writeBit)
{
    Simulator::insertPage(pageIndex, writeBit);
    pageOrder.push(pageIndex);
}
