/**
 * @file FIFOsim.cpp
 * @brief Implementation of the Fifo policy simulator
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 */
#include "FIFOsim.h"

/**
 * @brief Constructor.  Same as the base class constructor
 * @param pageSize The size of each page entry
 * @param memSize The size of the physical memory
 * @param logMemSize The size of the logical memory
 */
FIFOsim::FIFOsim(int pageSize, int memSize, int logMemSize) :
    Simulator(pageSize, memSize, logMemSize)
{

}

/**
 * @brief Destructor.
 */
FIFOsim::~FIFOsim()
{

}

/**
 * @brief The page replacement policy.  Finds which page was added earliest
 *        and removes that page, inserting a replacement
 * @param pageIndex The index of the page to insert
 * @param isWrite Whether the page being inserted will have a set dirty bit
 */
void FIFOsim::replacePage(int pageIndex, bool isWrite)
{
    // Get the location of the page to replace
    int repLocation = _pageOrder.front();
    // Remove that page from the list of when pages were inserted
    _pageOrder.pop();

    _pageFaults++;

    // Remove victim page and insert new page
    //cout << "Replacing " << repLocation << " with " << pageIndex << endl;
    if (_pageTable[repLocation].getDirtyBit()) {
        _numFlushes++;
    }
    _pageTable[repLocation].setValidBit(false);
    _pageTable[repLocation].setDirtyBit(false);

    _pageTable[pageIndex].setDirtyBit(isWrite);
    _pageTable[pageIndex].setValidBit(true);

    // Add new page to keep track of when it was inserted
    _pageOrder.push(pageIndex);
}

/**
 * @brief Behaves the same way as the base class, but adds the capability
 *        of tracking which pages were inserted first
 * @param pageIndex The index of the page to insert
 * @param isWrite Whether the page being inserted will have a set dirty bit
 */
void FIFOsim::insertPage(int pageIndex, bool writeBit)
{
    Simulator::insertPage(pageIndex, writeBit);
    _pageOrder.push(pageIndex);
}
