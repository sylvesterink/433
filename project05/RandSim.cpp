/**
 * @file RandSim.cpp
 * @brief The implementation of the random replacement simulator
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 */
#include "RandSim.h"

/**
 * @brief Constructor.  Same as the base class constructor,
 *        initializes randomizer
 * @param pageSize The size of each page entry
 * @param memSize The size of the physical memory
 * @param logMemSize The size of the logical memory
 */
RandSim::RandSim(int pageSize, int memSize, int logMemSize) :
    Simulator(pageSize, memSize, logMemSize)
{
    // Seed randomizer
    srand( time(NULL) );
}

/**
 * @brief Destructor
 */
RandSim::~RandSim()
{

}

/**
 * @brief The page replacement policy.  Randomly selects a page in use as the
 *        victim page and replaces it
 * @param pageIndex The index of the page to insert
 * @param isWrite Whether the page being inserted will have a set dirty bit
 */
void RandSim::replacePage(int pageIndex, bool isWrite)
{
    // Randomly choose a page from the list of valid pages
    // then use that value as the index value of the victim page
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

/**
 * @brief Behaves the same way as the base class, but keeps a list of the
 *        valid pages as they are inserted
 * @param pageIndex The index of the page to insert
 * @param isWrite Whether the page being inserted will have a set dirty bit
 */
void RandSim::insertPage(int pageIndex, bool writeBit)
{
    Simulator::insertPage(pageIndex, writeBit);
    _validPages.push_back(pageIndex);
}
