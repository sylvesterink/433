Simulator::Simulator(int pageSize, int memSize, int logMemSize) :
    _maxPages(logMemSize - pageSize),
    _pageSize(pageSize),
    _memReferences(0),
    _pageFault(0),
    _numFlushe(0),
    _totalTim(0)
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

