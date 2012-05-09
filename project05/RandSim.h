/**
 * @file RandSim.h
 * @brief The declaration of the random replacement simulation
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 */
#ifndef RANDSIM_H
#define RANDSIM_H

#include <cstdlib>
#include <vector>

using namespace std;
#include "Simulator.h"

/**
 * @brief A simulator that randomly chooses which page to replace
 */
class RandSim : public Simulator
{
    public:
        RandSim(int pageSize, int memSize, int logMemSize);
        virtual ~RandSim();

        virtual void replacePage(int pageIndex, bool isWrite);
        virtual void insertPage(int pageIndex, bool writeBit);

    private:
        // A list of all the currently occupied pages and their indices
        vector<int> _validPages;
};



#endif /* end of include guard: RANDSIM_H */
