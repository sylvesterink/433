#include "FIFOsim.h"

FIFOsim::FIFOsim(int pageSize, int memSize, int logMemSize) :
    Simulator(pageSize, memSize, logMemSize)
{

}

FIFOsim::~FIFOsim()
{

}

void FIFOsim::run(string &fileData)
{
    int testInt;

    stringstream converter(fileData);
    while ( !(converter >> testInt).fail() ) {
        cout << testInt << endl;
    }
}
