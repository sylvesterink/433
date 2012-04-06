#include <iostream>
#include <pthread.h>

#include "Buffer.h"

using namespace std;

int main(int argc, const char *argv[])
{
    // Make sure commandline arguments are valid
    if (argc < 3) {
        cout << "Usage: " << argv[0]
            << " [NUMBER OF PRODUCERS] [NUMBER OF CONSUMERS]" << endl;
        return -1;
    }

    Buffer test;
    int dummy;

    if (test.removeItem(dummy)) {
        cout << "Removed " << dummy << endl;
    }

    for (int i = 0; i < 6; i++) {
        if (test.insertItem(i) ) {
            cout << "Inserted " << i << endl;
        }
        else {
            cout << "Could Not Insert " << i << endl;
        }
    }

    for (int i = 0; i < 6; i++) {
        if (test.removeItem(dummy) ) {
            cout << "Removed " << dummy << endl;
        }
        else {
            cout << "Could Not Remove " << i << endl;
        }
    }

    return 0;
}

