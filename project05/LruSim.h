#ifndef LRUSIM_H
#define LRUSIM_H

#include "Simulator.h"

class LruSim : public Simulator
{
    public:
        LruSim(int pageSize, int memSize, int logMemSize);
        virtual ~LruSim();

        virtual void replacePage(int pageIndex, bool isWrite);
        virtual void insertPage(int pageIndex, bool writeBit);

    private:
        /* data */
};


#endif /* end of include guard: LRUSIM_H */
