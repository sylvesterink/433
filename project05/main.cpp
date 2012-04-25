#include <iostream>
#include <cstdlib> // For atoi()

using namespace std;

int main(int argc, const char *argv[])
{
    // Make sure commandline arguments are valid
    if (argc < 4) {
        cout << "Usage: " << argv[0]
            << " [POLICY TYPE] [PAGE SIZE (8-13)] [PHYSICAL MEM SIZE]" << endl;
        return -1;
    }

    //get parameter values
    int policyType = atoi(argv[1]);
    int pageSize = atoi(argv[2]);
    int memSize = atoi(argv[3]);

    //Check for invalid parameters
    if ( (policyType < 0) || (policyType > 2) ) {
        cout << "Error: Invalid policy type." << endl;
    }
    if ( (pageSize < 8) || (pageSize > 13) ) {
        cout << "Error: Page size must be from 8-13." << endl;
    }
    //if ( (memSize < 2) || ((memSize & (memSize - 1)) != 0) ) {
    if ( (memSize < 2) || (memSize > 31) ) {
        cout << "Error: Physical memory size must from 2-31." << endl;
    }

    return 0;
}
