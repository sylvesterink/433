#include <iostream>
#include <cstdlib> // For rand()
#include <pthread.h>

#include "Buffer.h"

using namespace std;

void *producer(void *param);
void *consumer(void *param);

int main(int argc, const char *argv[])
{
    vector<pthread_t> producerTid;
    vector<pthread_t> consumerTid;

    // Make sure commandline arguments are valid
    if (argc < 4) {
        cout << "Usage: " << argv[0]
            << " [RUNTIME IN SECONDS] [NUMBER OF PRODUCERS] [NUMBER OF CONSUMERS]" << endl;
        return -1;
    }

    int runtime = atoi(argv[1]);
    int numProducers = atoi(argv[2]);
    int numConsumers = atoi(argv[3]);

    if (runtime < 1) {
        cout << "Error: Runtime too small." << endl;
    }
    if (numProducers < 1) {
        cout << "Error: Not enough producers." << endl;
    }
    if (numConsumers < 1) {
        cout << "Error: Not enough consumers." << endl;
    }

    // Initialize Buffer
    Buffer test;

    // Create Producer Threads
    for (int i = 0; i < numProducers; i++) {
        pthread_t newId;
        pthread_create(&newId, NULL, producer, NULL);
        producerTid.push_back(newId);
    }

    // Create Consumer Threads
    for (int i = 0; i < numConsumers; i++) {
        pthread_t newId;
        pthread_create(&newId, NULL, consumer, NULL);
        consumerTid.push_back(newId);
    }

    // Sleep
    sleep(3);

    // Delete threads
    //while ( !producerTid.empty() ) {
        //pthread_t tid = producerTid.back();
        //producerTid.pop_back();
        //pthread_cancel(tid);
    //}

    //while ( !consumerTid.empty() ) {
        //pthread_t tid = consumerTid.back();
        //consumerTid.pop_back();
        //pthread_cancel(tid);
    //}

    // Exit
    return 0;
}

void *producer(void *param)
{
    void * returnValue = NULL;

    timespec sleepTime;
    sleepTime.tv_sec = 0;

    while (true) {
        sleepTime.tv_nsec = 500000000; // One Second
        nanosleep(&sleepTime, (struct timespec *)NULL);
        cout << "OMG PRODUCE!!!\n";
        cout << flush;
    }

    return returnValue;
}

void *consumer(void *param)
{
    void *returnValue = NULL;

    timespec sleepTime;
    sleepTime.tv_sec = 0;

    while (true) {
        sleepTime.tv_nsec = 100000000;
        nanosleep(&sleepTime, (struct timespec *)NULL);
        cout << "I consume.\n";
        cout << flush;
    }

    return returnValue;
}
