#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <sys/time.h>

#include "Page.h"
using namespace std;

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
        unsigned int _bitMask;

        vector<Page> _pageTable;

        // Final statistics
        int _numMemReferences;
        int _pageFaults;
        int _numFlushes;
        //int _totalTime;
};


#endif /* end of include guard: SIMULATOR_H */
