#ifndef FIFOSIM_H
#define FIFOSIM_H

#include "Simulator.h"

class FIFOsim : public Simulator
{
public:
    FIFOsim(int pageSize, int memSize, int logMemSize);
    virtual ~FIFOsim();

    virtual void run(string &fileData);
private:
    /* data */
};



#endif /* end of include guard: FIFOSIM_H */
