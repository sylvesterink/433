#ifndef FIFOSIM_H
#define FIFOSIM_H

#include <queue>

using namespace std;

#include "Simulator.h"

class FIFOsim : public Simulator
{
    public:
        FIFOsim(int pageSize, int memSize, int logMemSize);
        virtual ~FIFOsim();

        virtual void replacePage(int pageIndex, bool isWrite);
        virtual void insertPage(int pageIndex, bool writeBit);

    private:
        queue<int> _pageOrder;
};


#endif /* end of include guard: FIFOSIM_H */
