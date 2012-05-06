#ifndef LRUSIM_H
#define LRUSIM_H

#include <list>
#include <algorithm>
using namespace std;

#include "Simulator.h"

class LruSim : public Simulator
{
    public:
        LruSim(int pageSize, int memSize, int logMemSize);
        virtual ~LruSim();

        virtual void replacePage(int pageIndex, bool isWrite);
        virtual void accessPage(int pageIndex, bool writeBit);
        virtual void insertPage(int pageIndex, bool writeBit);

    private:
        list<int> _useOrder;
};


#endif /* end of include guard: LRUSIM_H */
