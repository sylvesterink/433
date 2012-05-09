/**
 * @file LruSim.cpp
 * @brief The implementation of the LRU object
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 */
#include "LruSim.h"

/**
 * @brief Constructor.  Same as the base class constructor
 * @param pageSize The size of each page entry
 * @param memSize The size of the physical memory
 * @param logMemSize The size of the logical memory
 */
LruSim::LruSim(int pageSize, int memSize, int logMemSize) :
    Simulator(pageSize, memSize, logMemSize)
{

}

/**
 * @brief Destructor.
 */
LruSim::~LruSim()
{

}

/**
 * @brief The page replacement policy.  Finds which page was used least
 *        recently and removes that page, inserting a replacement
 * @param pageIndex The index of the page to insert
 * @param isWrite Whether the page being inserted will have a set dirty bit
 */
void LruSim::replacePage(int pageIndex, bool isWrite)
{
    // The index of the least recently used page
    int repLocation = _useOrder.front();
    _useOrder.pop_front();

    _pageFaults++;

    //cout << "Replacing " << repLocation << " with " << pageIndex << endl;
    if (_pageTable[repLocation].getDirtyBit()) {
        _numFlushes++;
    }
    _pageTable[repLocation].setValidBit(false);
    _pageTable[repLocation].setDirtyBit(false);

    _pageTable[pageIndex].setDirtyBit(isWrite);
    _pageTable[pageIndex].setValidBit(true);

    _useOrder.push_back(pageIndex);
}

/**
 * @brief Behaves the same way as the base class, but adds the capability
 *        of tracking which pages were recently accessed
 * @param pageIndex The index of the page to insert
 * @param isWrite Whether the page being inserted will have a set dirty bit
 */
void LruSim::accessPage(int pageIndex, bool writeBit)
{
    Simulator::accessPage(pageIndex, writeBit);

    list<int>::iterator pos;

    // Searches through the recently used list to find the index being
    // accessed, then moves it to the back of the list, as it was just
    // recently accessed
    pos = find(_useOrder.begin(), _useOrder.end(), pageIndex);
    _useOrder.erase(pos);
    _useOrder.push_back(pageIndex);
}

/**
 * @brief Behaves the same way as the base class, but adds the capability
 *        of tracking which pages were recently inserted
 * @param pageIndex The index of the page to insert
 * @param isWrite Whether the page being inserted will have a set dirty bit
 */
void LruSim::insertPage(int pageIndex, bool writeBit)
{
    Simulator::insertPage(pageIndex, writeBit);

    _useOrder.push_back(pageIndex);
}
