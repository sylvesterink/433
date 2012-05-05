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
    int repLocation = rand() % _maxUsedPages + 1;

    _pageFaults++;

    int tableSize = _pageTable.size();
    for (int i = 0; i < tableSize; i++) {
        if (_pageTable[i].isValid()) {
            repLocation--;
            if (repLocation == 0) {
                if (_pageTable[i].getDirtyBit()) {
                    _numFlushes++;
                }
                _pageTable[i].setValidBit(false);
                _pageTable[i].setDirtyBit(false);
                break;
            }
        }
    }

    _pageTable[pageIndex].setDirtyBit(isWrite);
    _pageTable[pageIndex].setValidBit(true);
}
