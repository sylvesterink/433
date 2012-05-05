#ifndef RANDSIM_H
#define RANDSIM_H

#include <cstdlib>
#include "Simulator.h"

class RandSim : public Simulator
{
    public:
        RandSim(int pageSize, int memSize, int logMemSize);
        virtual ~RandSim();

        virtual void replacePage(int pageIndex, bool isWrite);
    private:
};



#endif /* end of include guard: RANDSIM_H */
