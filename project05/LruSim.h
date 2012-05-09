/**
 * @file LruSim.h
 * @brief The declaration of the Lru simulation object
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 */
#ifndef LRUSIM_H
#define LRUSIM_H

#include <list>
#include <algorithm>
using namespace std;

#include "Simulator.h"

/**
 * @brief A simulator that uses the LRU replacement policy
 */
class LruSim : public Simulator
{
    public:
        LruSim(int pageSize, int memSize, int logMemSize);
        virtual ~LruSim();

        virtual void replacePage(int pageIndex, bool isWrite);
        virtual void accessPage(int pageIndex, bool writeBit);
        virtual void insertPage(int pageIndex, bool writeBit);

    private:
        // A list of which page was used most recently
        list<int> _useOrder;
};


#endif /* end of include guard: LRUSIM_H */
