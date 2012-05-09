/**
 * @file FIFOsim.h
 * @brief The declaration of the FIFO replacement policy simulation
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 */
#ifndef FIFOSIM_H
#define FIFOSIM_H

#include <queue>

using namespace std;

#include "Simulator.h"

/**
 * @brief A simulator that uses the FIFO replacement policy
 */
class FIFOsim : public Simulator
{
    public:
        FIFOsim(int pageSize, int memSize, int logMemSize);
        virtual ~FIFOsim();

        virtual void replacePage(int pageIndex, bool isWrite);
        virtual void insertPage(int pageIndex, bool writeBit);

    private:
        // Used to keep track of which page was added first
        queue<int> _pageOrder;
};


#endif /* end of include guard: FIFOSIM_H */
