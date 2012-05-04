#include "Simulator.h"

Simulator::Simulator(int pageSize, int memSize, int logMemSize) :
    _maxPages(logMemSize - pageSize), // all values are powers of 2, including maxpages
    _pageSize(pageSize),
    _bitMask(0),
    _memReferences(0),
    _pageFaults(0),
    _numFlushes(0),
    _totalTime(0)
{
    _bitMask = (_bitMask - 1) << pageSize;
}

Simulator::~Simulator()
{

}

bool Simulator::isWrite(int memReference)
{
    if ( memReference % 2 == 1 ) {
        return true;
    }

    return false;
}
