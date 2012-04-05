#include <iostream>
#include <pthread.h>

using namespace std;

int main(int argc, const char *argv[])
{
    // Make sure commandline arguments are valid
    if (argc < 3) {
        cout << "Usage: " << argv[0]
            << " [NUMBER OF PRODUCERS] [NUMBER OF CONSUMERS]" << endl;
        return -1;
    }

    return 0;
}
