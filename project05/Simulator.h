#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>

using namespace std;

class Simulator
{
public:
    Simulator(int pageSize, int memSize);
    ~Simulator();

    void run() = 0;

private:
    vector<Page> pageTable;

    // Final statistics
    int memReferences;
    int pageFaults;
    int numFlushes;
    int totalTime;
};


#endif /* end of include guard: SIMULATOR_H */
