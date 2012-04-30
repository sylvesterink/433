#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>

using namespace std;

class Simulator
{
public:
    Simulator(int pageSize, int memSize, int logMemSize);
    ~Simulator();

    void run() = 0;

private:
    vector<Page> _pageTable;
    int _maxPages;
    int _pageSize;

    // Final statistics
    int _memReferences;
    int _pageFaults;
    int _numFlushes;
    int _totalTime;
};


#endif /* end of include guard: SIMULATOR_H */
