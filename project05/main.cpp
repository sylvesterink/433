/**
 * @file main.cpp
 * @brief Simulates a paging system with different page replacement algorithms.
 *        Currently implements Random, FIFO, and LRU replacement.
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0
 * @date 2012-05-08
 * @course CS433
 * @assignment 5
 * @compilation make
 */
#include <iostream>
#include <fstream>
#include <cstdlib> // For atoi()

#include "FIFOsim.h"
#include "RandSim.h"
#include "LruSim.h"

using namespace std;

// Logical memory size is constant in this case
static const int LOGICAL_MEM_SIZE = 27;

// The different types of replacement algorithms
enum {
    P_RAND,
    P_FIFO,
    P_LRU
};

// Function declarations
bool readFile(const char *fileName, string &fileData);

/**
 * @brief Main function. Gets policy type, page size, and physical memory size.
 *        Then runs the appropriate simulation.
 * @param argc Number of arguments passed.
 * @param argv[] Runtime arguments.
 * @return Success or failure of program.
 */
int main(int argc, const char *argv[])
{
    // Make sure commandline arguments are valid
    if (argc < 4) {
        cout << "Usage: " << argv[0]
            << " [POLICY TYPE (0=Rand, 1=Fifo, 2=LRU] [PAGE SIZE (8-13)] [PHYSICAL MEM SIZE (2-31)]" << endl;
        return -1;
    }

    //get parameter values
    int policyType = atoi(argv[1]);
    int pageSize = atoi(argv[2]);
    int memSize = atoi(argv[3]);

    //Check for invalid parameters
    if ( (policyType < 0) || (policyType > 2) ) {
        cout << "Error: Invalid policy type." << endl;
        return -1;
    }
    if ( (pageSize < 2) || (pageSize > 13) ) {
        cout << "Error: Page size must be from 2-13." << endl;
        return -1;
    }
    if ( (memSize < 8) || (memSize > 31) ) {
        cout << "Error: Physical memory size must from 8-31." << endl;
        return -1;
    }
    if ( memSize < pageSize ) {
        cout << "Error: Physical memory must be larger than page size." << endl;
        return -1;
    }

    cout << "Page Table Simulator" << endl;
    cout << "Cavan Crawford and Brandon Kasa\n" << endl;

    // Open the data file and run the appropriate simulation on it
    string fileData;
    if (readFile("references.txt", fileData)) {
        if (policyType == P_RAND) {
            cout << "Using Random replacement policy." << endl;
            RandSim rand(pageSize, memSize, LOGICAL_MEM_SIZE);
            rand.run(fileData);
        }
        else if (policyType == P_FIFO) {
            cout << "Using FIFO replacement policy." << endl;
            FIFOsim fifo(pageSize, memSize, LOGICAL_MEM_SIZE);
            fifo.run(fileData);
        }
        else if (policyType == P_LRU) {
            cout << "Using LRU replacement policy." << endl;
            LruSim lru(pageSize, memSize, LOGICAL_MEM_SIZE);
            lru.run(fileData);
        }
    }
    else {
        cout << "Error: File \"references.txt\" missing" << endl;
        return -1;
    }

    return 0;
}

/**
 * @brief Reads a file and stores the data in a string
 * @param fileName The name of the file to read
 * @param fileData The string to store the file data in
 * @return Whether the file was successfully read or not
 */
bool readFile(const char *fileName, string &fileData)
{
    ifstream fin;
    string input;

    cout << "Loading File..." << flush;
    fin.open(fileName);

    // Read the file line by line into the string
    if (fin.is_open()) {
        while (!fin.eof()) {
            getline(fin, input);
            fileData += input + " ";
        }
    }
    else {
        return false;
    }

    fin.close();
    cout << "File Loaded\n" << endl;

    return true;
}
