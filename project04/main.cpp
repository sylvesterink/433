#include <iostream>
#include <cstdlib> // For rand()
#include <pthread.h>

#include "Buffer.h"

using namespace std;

void *producer(void *param);
void *consumer(void *param);

pthread_mutex_t bufferMutex = PTHREAD_MUTEX_INITIALIZER;

static const int BUFFER_SIZE = 5;
Buffer sharedBuffer(BUFFER_SIZE);

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
    srand( time(NULL) );

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
    sleep(runtime);

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
        // Random number between 100 milliseconds and 1 second
        sleepTime.tv_nsec = rand() % 999999999 + 100000000;
        nanosleep(&sleepTime, (struct timespec *)NULL);

        int newItem = rand() % 99;

        sleepTime.tv_nsec = rand() % 100000000;
        bool waitingToProduce = true;
        while ( waitingToProduce ) {
            pthread_mutex_lock(&bufferMutex);
            if ( !sharedBuffer.isFull() ) {
                if ( sharedBuffer.insertItem(newItem) ) {
                    cout << "+ " << newItem << " inserted by producer. ";
                    sharedBuffer.displayBuffer();
                }
                else {
                    cout << "Error: Failed to insert into shared buffer.\n";
                }

                cout << flush;
                waitingToProduce = false;
            }
            pthread_mutex_unlock(&bufferMutex);
        } //wait
    }
    return returnValue;
}

void *consumer(void *param)
{
    void *returnValue = NULL;

    timespec sleepTime;
    sleepTime.tv_sec = 0;

    while (true) {
        // Random number between 100 milliseconds and 1 second
        sleepTime.tv_nsec = rand() % 999999999 + 100000000;
        nanosleep(&sleepTime, (struct timespec *)NULL);

        int removedItem = 0;

        bool waitingToConsume = true;
        while ( waitingToConsume ) {
            pthread_mutex_lock(&bufferMutex);
            if ( !sharedBuffer.isEmpty() ) {
                if ( sharedBuffer.removeItem(removedItem) ) {
                    cout << "- " << removedItem << " removed by consumer. ";
                    sharedBuffer.displayBuffer();
                }
                else {
                    cout << "Error: Failed to remove from shared buffer.\n";
                }

                cout << flush;
                waitingToConsume = false;
            }
            pthread_mutex_unlock(&bufferMutex);
        } //wait
    }
    return returnValue;
}
