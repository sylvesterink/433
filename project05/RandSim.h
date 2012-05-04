#ifndef RANDSIM_H
#define RANDSIM_H

#include "Simulator.h"

class RandSim : public Simulator
{
    public:
        RandSim(int pageSize, int memSize, int logMemSize);
        virtual ~RandSim();

        virtual void run(string &fileData);
    private:
        vector<Page> _pageTable;
};



#endif /* end of include guard: RANDSIM_H */
