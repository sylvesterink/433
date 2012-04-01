#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "FCFSSystem.h"
#include "SJFSystem.h"

static const int MAX_RUNTIME = 300000; // 5 minutes in milliseconds

int main(int argc, const char *argv[])
{
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " [NUMPROCESSES] [-FCFS | -SJF]" << endl;
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

    for (int i = 2; i < argc; i++) {
        if ( strcmp(argv[i], "-FCFS") == 0 ) {
            FCFSSystem simFCFSSystem;
            simFCFSSystem.simulation(numProcesses, MAX_RUNTIME);
        }

        if ( strcmp(argv[i], "-SJF") == 0 ) {
            SJFSystem simSJFSystem;
            simSJFSystem.simulation(numProcesses, MAX_RUNTIME);
        }
    }

    return 0;
}

