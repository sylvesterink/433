#include "RandSim.h"

RandSim::RandSim(int pageSize, int memSize, int logMemSize) :
    Simulator(pageSize, memSize, logMemSize)
{
    _pageTable.reserve(_maxPages);
}

RandSim::~RandSim()
{

}

void RandSim::run(string &fileData)
{
    int memReference;
    int pageIndex = 0;

    stringstream converter(fileData);
    while ( !(converter >> memReference).fail() ) {
        pageIndex = (memReference & _bitMask) >> _pageSize;
        if( isWrite(memReference) ) {
            //is write, set dirty bit
        }
    }
}
