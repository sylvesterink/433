#include "Simulator.h"

Simulator::Simulator(int pageSize, int memSize, int logMemSize) :
    _maxPages(logMemSize - pageSize),
    _pageSize(pageSize),
    _memReferences(0),
    _pageFaults(0),
    _numFlushes(0),
    _totalTime(0)
{
    _pageTable.reserve(_maxPages);

    //_maxPages = logMemSize - pageSize;
    //_pageSize = pageSize;

    //_memReferences = 0;
    //_pageFaults = 0;
    //_numFlushes = 0;
    //_totalTime = 0;

}

Simulator::~Simulator()
{

}

