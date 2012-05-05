#ifndef RANDSIM_H
#define RANDSIM_H

#include <cstdlib>
#include <vector>

using namespace std;
#include "Simulator.h"

class RandSim : public Simulator
{
    public:
        RandSim(int pageSize, int memSize, int logMemSize);
        virtual ~RandSim();

        virtual void replacePage(int pageIndex, bool isWrite);
        virtual void insertPage(int pageIndex, bool writeBit);

    private:
        vector<int> _validPages;
};



#endif /* end of include guard: RANDSIM_H */
