#include "Simulator.h"

Simulator::Simulator(int pageSize, int memSize, int logMemSize) :
    _numPages(logMemSize - pageSize), // all values are powers of 2, including numpages
    _usedPages(0),
    _maxUsedPages( 1 << (memSize - pageSize) ),
    _pageSize(pageSize),
    _bitMask(0),
    _numMemReferences(0),
    _pageFaults(0),
    _numFlushes(0)
{
    unsigned int intNumPages = 1 << _numPages;

    _bitMask = (_bitMask - 1) << pageSize;
    _pageTable.reserve(intNumPages);

    Page newPage;
    for (unsigned int i = 0; i < intNumPages; i++) {
        _pageTable.push_back(newPage);
    }

    cout << "Number of Pages " << intNumPages << endl;
    cout << "Pow Number of Pages " << _numPages << endl;
    cout << "Max usable pages " << _maxUsedPages << endl;
    cout << "Pow Page Size " << _pageSize << endl;
    cout << "Bitmask " << hex << _bitMask << dec << endl;
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

void Simulator::run(string &fileData)
{
    int memReference;
    int pageIndex = 0;

    // Set up variables to be used for estimating runtime
    timeval endTime;
    timeval startTime;

    // Get the start time of the loop
    gettimeofday(&startTime, NULL);

    stringstream converter(fileData);
    while ( !(converter >> memReference).fail() ) {
        pageIndex = (memReference & _bitMask) >> _pageSize;
        _numMemReferences++;
        bool writeBit = isWrite(memReference);

        //cout << memReference << ", " << pageIndex << endl;
        if (_pageTable[pageIndex].isValid()) {
            //cout << "Valid" << endl;
            accessPage(pageIndex, writeBit);
        }
        else if ( _usedPages < _maxUsedPages ) {
            //cout << "Writing at " << pageIndex << endl;
            insertPage(pageIndex, writeBit);
        }
        else {
            replacePage(pageIndex, writeBit);
        }
    }

    // Get ending time of the loop
    gettimeofday(&endTime, NULL);

    // Convert the times to seconds
    double initialTime = startTime.tv_sec+(startTime.tv_usec/1000000.0);
    double finalTime = endTime.tv_sec+(endTime.tv_usec/1000000.0);

    cout << "Total Memory References: " << _numMemReferences << endl;
    cout << "Total Page Faults: " << _pageFaults << endl;
    cout << "Total Flushes: " << _numFlushes << endl;

    // Calculate and display the duration
    cout << "Total Simulation Time: " << finalTime - initialTime << " seconds." << endl;
}

void Simulator::accessPage(int pageIndex, bool writeBit)
{
    if( writeBit ) {
        _pageTable[pageIndex].setDirtyBit(true);
    }
}

void Simulator::insertPage(int pageIndex, bool writeBit)
{
    if( writeBit ) {
        _pageTable[pageIndex].setDirtyBit(true);
    }
    _pageTable[pageIndex].setValidBit(true);
    _usedPages++;
}
