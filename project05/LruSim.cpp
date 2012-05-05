#include "LruSim.h"

LruSim::LruSim(int pageSize, int memSize, int logMemSize) :
    Simulator(pageSize, memSize, logMemSize)
{

}

LruSim::~LruSim()
{

}

void LruSim::replacePage(int pageIndex, bool isWrite)
{

}

void LruSim::insertPage(int pageIndex, bool writeBit)
{
    Simulator::insertPage(pageIndex, writeBit);
}
