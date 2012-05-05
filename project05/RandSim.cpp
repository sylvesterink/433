#include "RandSim.h"

RandSim::RandSim(int pageSize, int memSize, int logMemSize) :
    Simulator(pageSize, memSize, logMemSize)
{
    // Seed randomizer
    srand( time(NULL) );
}

RandSim::~RandSim()
{

}

void RandSim::replacePage(int pageIndex, bool isWrite)
{
    int repIndex = rand() % _validPages.size();
    int repLocation = _validPages[repIndex];

    _pageFaults++;

    //cout << "Replacing " << repLocation << " with " << pageIndex << endl;
    if (_pageTable[repLocation].getDirtyBit()) {
        _numFlushes++;
    }
    _pageTable[repLocation].setValidBit(false);
    _pageTable[repLocation].setDirtyBit(false);

    _pageTable[pageIndex].setDirtyBit(isWrite);
    _pageTable[pageIndex].setValidBit(true);
    
    _validPages[repIndex] = pageIndex;
}

void RandSim::insertPage(int pageIndex, bool writeBit)
{
    Simulator::insertPage(pageIndex, writeBit);
    _validPages.push_back(pageIndex);
}
