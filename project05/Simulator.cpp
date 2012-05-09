/**
 * @file Simulator.cpp
 * @brief Implementation of the base simulation object
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 */
#include "Simulator.h"

/**
 * @brief Constructor.  Sets basic values according to the arguments and
 *        initializes the page table.  Outputs the settings for the simulation.
 * @param pageSize The size of each page entry
 * @param memSize The size of the physical memory
 * @param logMemSize The size of the logical memory
 */
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
    //cout << "Bitmask " << hex << _bitMask << dec << "\n" << endl;
}

/**
 * @brief Destructor.
 */
Simulator::~Simulator()
{

}

/**
 * @brief Checks if the memory reference is to be written
 * @param memReference The memory reference to check
 * @return Returns whether this is a write value or not
 */
bool Simulator::isWrite(int memReference)
{
    if ( memReference % 2 == 1 ) {
        return true;
    }

    return false;
}

/**
 * @brief Runs the simulation by reading the memory reference and choosing
 *        whether to write it to the pagetable, update the access values,
 *        or replace another page
 * @param fileData The list of memory references
 */
void Simulator::run(string &fileData)
{
    int memReference;
    int pageIndex = 0;

    // Set up variables to be used for estimating runtime
    timeval endTime;
    timeval startTime;

    cout << "Running Simulation..." << flush;
    // Get the start time of the loop
    gettimeofday(&startTime, NULL);

    // Read each memory reference and determine whether to write, access,
    // or replace
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

    // Output the simulation results
    cout << "Simulation Complete\n" << endl;
    cout << "Total Memory References: " << _numMemReferences << endl;
    cout << "Total Page Faults: " << _pageFaults << endl;
    cout << "Total Flushes: " << _numFlushes << endl;

    // Calculate and display the duration
    cout << "Total Simulation Time: " << finalTime - initialTime << " seconds." << endl;
}

/**
 * @brief Update this reference in the pagetable
 * @param pageIndex The index of the page to update
 * @param writeBit Whether this reference contains a write value
 */
void Simulator::accessPage(int pageIndex, bool writeBit)
{
    if( writeBit ) {
        _pageTable[pageIndex].setDirtyBit(true);
    }
}

/**
 * @brief Insert a new page in the table
 * @param pageIndex The index of the page to update
 * @param writeBit Whether this reference contains a write value
 */
void Simulator::insertPage(int pageIndex, bool writeBit)
{
    if( writeBit ) {
        _pageTable[pageIndex].setDirtyBit(true);
    }
    _pageTable[pageIndex].setValidBit(true);
    _usedPages++;
}
