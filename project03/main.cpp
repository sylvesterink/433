#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

#include "FCFSSystem.h"

static const int MAX_RUNTIME = 300000; // 5 minutes in milliseconds

void simulation(int numProcesses, System* simSystem);

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " [NUMPROCESSES]" << endl;
        return 1;
    }

    int numProcesses = atoi(argv[1]);

    if (numProcesses < 1) {
        cerr << "Too few processes!" << endl;
        return 1;
    }

    cout << "Discrete Event Simulator" << endl;
    cout << "Cavan Crawford and Brandon Kasa" << endl;

    srand( time(NULL) );

    FCFSSystem simSystem;
    simSystem.simulation(numProcesses, MAX_RUNTIME);

    return 0;
}

