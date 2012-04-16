/*
 * @file main.cpp
 * @brief A simulation to solve the producer/consumer problem having
 *        multiple producer and consumer threads.
 * @author Cavan Crawford and Brandon Kasa
 * @version 1.0 
 * @date 2012-04-18
 * @course CS433
 * @assignment 4
 * @compilation make
 */
#include <iostream>
#include <cstdlib> // For rand()
#include <pthread.h>

//Shared resource class
#include "Buffer.h"

using namespace std;

//Function Declarations
void *producer(void* nullParam);
void *consumer(void* nullParam);

//Shared resource mutex
pthread_mutex_t bufferMutex = PTHREAD_MUTEX_INITIALIZER;

//Restrict buffer size
static const int BUFFER_SIZE = 5;
Buffer sharedBuffer(BUFFER_SIZE);

/**
 * @brief Main function. Gets simulation duration, the number of producers, and 
 *        number of consumers
 * @param argc Number of parameters passed
 * @param argv[] Runtime parameters
 * @return Success or failure of program
 */
int main(int argc, const char *argv[])
{
    //Vectors to hold the threads
    vector<pthread_t> producerTid;
    vector<pthread_t> consumerTid;

    // Make sure commandline arguments are valid
    if (argc < 4) {
        cout << "Usage: " << argv[0]
            << " [RUNTIME IN SECONDS] [NUMBER OF PRODUCERS] [NUMBER OF CONSUMERS]" << endl;
        return -1;
    }

    //get parameter values
    int runtime = atoi(argv[1]);
    int numProducers = atoi(argv[2]);
    int numConsumers = atoi(argv[3]);

    //Check for invalid parameters
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

    // Sleep while threads are running
    sleep(runtime);

    //Terminate threads
    while ( !producerTid.empty() ) {
       pthread_t tid = producerTid.back();
       producerTid.pop_back();
       pthread_cancel(tid);
    }

    while ( !consumerTid.empty() ) {
        pthread_t tid = consumerTid.back();
        consumerTid.pop_back();
        pthread_cancel(tid);
    }

    // Exit
    return 0;
}

/**                                                                                            
 * @brief Entry point for newly created producer threads. Each thread will generate a random
          number and wait on the mutex to use the resource. The number is added to the buffer
 */
void *producer(void* nullParam)
{
    //Time struct used for witing
    timespec sleepTime;
    sleepTime.tv_sec = 0;

    //Thread will run untill terminated
    while (true) {
        // Random number between 100 milliseconds and 1 second
        sleepTime.tv_nsec = rand() % 999999999 + 100000000;
        nanosleep(&sleepTime, (struct timespec *)NULL);

        int newItem = rand() % 99; //Item to add to buffer

        bool waitingToProduce = true;
        while ( waitingToProduce ) {
	    //Wait on mutex
            pthread_mutex_lock(&bufferMutex); 
            if ( !sharedBuffer.isFull() ) {
	        //add item to buffer
                if ( sharedBuffer.insertItem(newItem) ) {
                    cout << "+ " << newItem << " inserted by producer. ";
                    sharedBuffer.displayBuffer();
                }
                else {
                    cout << "Error: Failed to insert into shared buffer.\n";
                }

                cout << flush; //Report action
                waitingToProduce = false;
            }
	    //release resource
            pthread_mutex_unlock(&bufferMutex);
        } //wait
    }
    return nullParam;
}

/*
 * @brief Entry point for newly created consumer threads.  Each thread will attempt to 
 *        retrieve the next element in the buffer and output its result
 */
void *consumer(void* nullParam)
{
    //Time struct use for waiting
    timespec sleepTime;
    sleepTime.tv_sec = 0;

    //Thread will loop until terminated
    while (true) {
        // Random number between 100 milliseconds and 1 second
        sleepTime.tv_nsec = rand() % 999999999 + 100000000;
        nanosleep(&sleepTime, (struct timespec *)NULL); //wait

        int removedItem = 0; //Item to be removed

        bool waitingToConsume = true;
	//loop until item is consumed
        while ( waitingToConsume ) {
	    //Wait on mutex
            pthread_mutex_lock(&bufferMutex);
            if ( !sharedBuffer.isEmpty() ) {
	        //Retrieve item from buffer
                if ( sharedBuffer.removeItem(removedItem) ) {
                    cout << "- " << removedItem << " removed by consumer. ";
                    sharedBuffer.displayBuffer();
                }
                else {
                    cout << "Error: Failed to remove from shared buffer.\n";
                }

                cout << flush; //Report action
                waitingToConsume = false;
            }
            pthread_mutex_unlock(&bufferMutex);
        }
    }
    return nullParam;
}
