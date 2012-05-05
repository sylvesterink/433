#include <iostream>
#include <fstream>
#include <cstdlib> // For atoi()

#include "FIFOsim.h"
#include "RandSim.h"

using namespace std;

//static const int LOGICAL_MEM_SIZE = 134217728;
static const int LOGICAL_MEM_SIZE = 27;
//static const int LOGICAL_MEM_SIZE = 5;

enum {
    P_RAND,
    P_FIFO,
    P_LRU
};

bool readFile(const char *fileName, string &fileData);

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
    //TODO: Uncomment this
    if ( (pageSize < 8) || (pageSize > 13) ) {
        cout << "Error: Page size must be from 8-13." << endl;
        return -1;
    }
    if ( (memSize < 2) || (memSize > 31) ) {
        cout << "Error: Physical memory size must from 2-31." << endl;
        return -1;
    }

    cout << "Page Table Simulator" << endl;
    cout << "Cavan Crawford and Brandon Kasa\n" << endl;

    string fileData;
    if (readFile("references.txt", fileData)) {
        if (policyType == P_RAND) {
            RandSim rand(pageSize, memSize, LOGICAL_MEM_SIZE);
            rand.run(fileData);
        }
        else if (policyType == P_FIFO) {
            FIFOsim fifo(pageSize, memSize, LOGICAL_MEM_SIZE);
            fifo.run(fileData);
        }
        else if (policyType == P_LRU) {
            //LRUsim lru(pageSize, memSize, LOGICAL_MEM_SIZE);
            //lru.run(fileData);
        }
    }
    else {
        cout << "Error: File \"references.txt\" missing" << endl;
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

    return true;
}
