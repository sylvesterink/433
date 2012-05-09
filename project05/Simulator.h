/**
 * @file Simulator.h
 * @brief Declarations for the Simulator object
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 */
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <sys/time.h>

#include "Page.h"
using namespace std;

/**
 * @brief Abstract class for various simulation types.  Implements the basic
 *        functions, not including replacement, which is determined by deriving
 *        classes.
 */
class Simulator
{
    public:
        Simulator(int pageSize, int memSize, int logMemSize);
        virtual ~Simulator();

        virtual void run(string &fileData);
        virtual void replacePage(int pageIndex, bool isWrite) = 0;
        virtual void accessPage(int pageIndex, bool writeBit);
        virtual void insertPage(int pageIndex, bool writeBit);

    protected:
        bool isWrite(int memReference);

    protected:
        int _numPages;
        int _usedPages;
        int _maxUsedPages;
        int _pageSize;
        unsigned int _bitMask; // Used in calculating page locations

        vector<Page> _pageTable;

        // Final statistics
        int _numMemReferences;
        int _pageFaults;
        int _numFlushes;
};


#endif /* end of include guard: SIMULATOR_H */
