/**
 * @file main.cpp
 * @brief Simulates a cpu scheduler using First Come First Serve,
 *        Shortest Job First, and Round Robin scheduling
 * @author Cavan Crawford & Brandon Kasa
 * @version 1.0
 * @date 2012-04-02
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "FCFSSystem.h"
#include "SJFSystem.h"
#include "RRSystem.h"

// Constants
static const int MAX_RUNTIME = 300000; // 5 minutes in milliseconds

/**
 * @brief Parses command line arguments and runs simulation with required
 *        scheduler.
 * @param argc Number of parameters
 * @param argv[] Command line arguments
 * @return Whether the program completed successfuly
 */
int main(int argc, const char *argv[])
{
    //    if (argc < 3) {
    //     cout << "Usage: " << argv[0] <<
    //	        " (NUMPROCESSES) [-FCFS &| -SJF &| -RR (Quantum)]" << endl;
    //      return 1;
    //  }

    int numProcesses = atoi(argv[1]);
    bool FCFS = false;
    bool SJF = false;
    bool RR = false;
    int quantum = 0;

    // Check if number of processes is valid
    if (numProcesses < 1) {
        cerr << "Too few processes!" << endl;
        return 1;
    }

    // Initialize randomizer
    srand( time(NULL) );

    // Select which schedulers to use
    for (int i = 2; i < argc; i++) {
        if ( strcmp(argv[i], "-FCFS") == 0 ) {
            FCFS = true;
            argv[i] = "";
        }

        if ( strcmp(argv[i], "-SJF") == 0 ) {
            SJF = true;
            argv[i] = "";
        }

        // RR scheduler has additional quantum requirement
        if ( strcmp(argv[i], "-RR") == 0 && argc > i + 1) {
            quantum = atoi(argv[i+1]);
            if (quantum > 0) {
                RR = true;
            }
            else {
                cout << "Invalid Quantum Value" << endl;
            }
            argv[i] = "";
            argv[i+1] = "";
        }
    }

    //Check for extra parameters
    for (int i = 2; i < argc; i++) {
        if ( strcmp(argv[i], "") != 0) {
            cout << "Usage: " << argv[0] <<
                " (NUMPROCESSES) [-FCFS &| -SJF &| -RR (Quantum)]" << endl;
            return 1;
        }
    }

    cout << "Discrete Event Simulator" << endl;
    cout << "Cavan Crawford and Brandon Kasa" << endl;

    // Run selected simulations
    if(FCFS){
        cout << "Simulating FCFS\n" << endl;
        FCFSSystem simFCFSSystem;
        simFCFSSystem.simulation(numProcesses, MAX_RUNTIME);
    }

    if(SJF){
        cout << "Simulating FCFS\n" << endl;
        SJFSystem simSJFSystem;
        simSJFSystem.simulation(numProcesses, MAX_RUNTIME);
    }

    if(RR){
        cout << "Simulating RR using quantum " << quantum  << "\n" << endl;
        RRSystem simSJFSystem(quantum);
        simSJFSystem.simulation(numProcesses, MAX_RUNTIME);
    }

    return 0;
}

