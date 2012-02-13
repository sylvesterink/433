/**
 * @file main.cpp
 * @brief The main driver to test the ReadyQueue object.
 *        Sets up Process Control Block structures and inserts them in the
 *        ReadyQueue, then performs a set number of operations testing the
 *        ReadyQueue's capabilities
 * @author Cavan Crawford, Brandon Kasa
 * @version 1.0
 * @date 2012-02-12
 * @course CS433
 * @assignment 1
 * @compilation make
 * @notes One of the goals of this assignment is that the program performs
 *        well, which would be better implemented in C rather than C++ to
 *        avoid the overhead introduced in C++. However, for readability
 *        this implementation was done in C++. Some objects, such as the
 *        PCB structure, were kept simple for the sake of performance.  In
 *        the long run, most of the objects would be abstracted into classes
 *        for better readability and control.
 */

#include <iostream>

// Time libraries used for calculating random numbers
// and getting run duration.
#include <ctime>
#include <cstdlib>
#include <sys/time.h>

using namespace std;

#include "PCB.h"
#include "ReadyQueue.h"

// Constant declarations
static const int TABLE_SIZE = 20;
static const int MAX_PRIORITY = 50;
static const int NUM_CYCLES = 1000000;

// Function declarations
bool initialize(PCB*);
void partOne(PCB*, ReadyQueue&);
void partTwo(PCB*, ReadyQueue&);

/**
 * @brief Main function. Initializes variables and calls tests.
 * @param argc Number of parameters passed
 * @param argv[] Program parameters
 * @return Success or failure of program
 */
int main(int argc, const char *argv[])
{
    // A dynamic array that will contain all the processes on the system
    PCB* PCB_table = NULL;

    cout << "Priority Queue" << endl;
    cout << "Cavan Crawford and Brandon Kasa" << endl;

    // Create a new array of the required size
    PCB_table = new PCB[TABLE_SIZE];
    // Create the ReadyQueue to be used
    ReadyQueue q1;

    // Initialize the array.
    if (initialize(PCB_table)) {
        partOne(PCB_table, q1);
    }

    // Reinitialize the array.
    if (initialize(PCB_table)) {
        partTwo(PCB_table, q1);
    }

    // Clean up the table once finished
    delete[] PCB_table;

    return 0;
}

/**
 * @brief Create the PCB_table and initialize its values
 * @param table
 * @return Whether initialization was a success
 */
bool initialize(PCB* table)
{
    if (table == NULL) {
        return false;
    }

    // Initialize the member variables of each struct
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].id = i + 1;

        //This sequential priority is used in part 1 only
        table[i].priority = i + 1;
        table[i].state = WAITING;
    }

    //initialize random number generator
    srand(time(0));

    return true;
}

/**
 * @brief Part 1 of the assignment.
 *        Tests the enqueue and dequeue of the ReadyQueue, ensuring that it
 *        works correctly
 * @param table The array of processes to queue
 */
void partOne(PCB* table, ReadyQueue& q1)
{
    // Test 1 in the assignment
    cout << "Test 1:" << endl;

    q1.insertProc(&table[4]);
    q1.insertProc(&table[0]);
    q1.insertProc(&table[7]);
    q1.insertProc(&table[10]);

    // Display the queue, then remove a process
    q1.displayQueue();
    q1.removeHighestProc();
    q1.displayQueue();

    // Add more processes to queue
    q1.insertProc(&table[2]);
    q1.insertProc(&table[6]);
    q1.insertProc(&table[1]);
    q1.insertProc(&table[11]);
    q1.insertProc(&table[8]);

    // Remove each process, displaying queue with each removal.
    while (!q1.isEmpty()) {
        q1.removeHighestProc();
        q1.displayQueue();
    }
}

/**
 * @brief Part 2 of the assingment.
 *        Tests that the ReadyQueue performs well. Adds and removes
 *        processes of random priorities over a number of cycles.
 *        When complete, displays the estimated processing time.
 * @param table The array of processes to queue
 */
void partTwo(PCB* table, ReadyQueue& q1)
{
    // Test 2 in the assignment
    cout << "\nTest 2:" << endl;

    // Random value, to be used in selecting processes from table
    int random = 0;

    // Add an initial batch of processes with random
    // priority from the process table.
    for(int i = 0; i < 10; i++) {
        random = (rand() % TABLE_SIZE);

        // If a process is already in the queue, try the next process in the table
        while (table[random].state == READY) {
            random = (random + 1) % TABLE_SIZE;
        }

        // Set the priority of the process to a random value
        table[random].priority = (rand() % MAX_PRIORITY) + 1;
        q1.insertProc(&table[random]);
    }

    // Set up variables to be used for estimating runtime
    timeval endTime;
    timeval startTime;

    // Get the start time of the loop
    gettimeofday(&startTime, NULL);

    // Iterate through a large number of cycles, inserting and removing
    // processes from the queue
    for(int i = 0; i < NUM_CYCLES; i++) {
        // Remove the highest priority item and age the remaining items
        cout << q1.removeHighestProc().id << endl;
        q1.displayQueue();
        q1.agePriority();

        // Insert a random process
        random = (rand() % TABLE_SIZE);

        // If a process is already in the queue, try the next process in the table
        while (table[random].state == READY) {
            random= (random + 1) % TABLE_SIZE;
        }

        // Set the priority of the process to a random value
        table[random].priority = (rand() % MAX_PRIORITY) + 1;
        q1.insertProc(&table[random]);
    }

    // Get ending time of the loop
    gettimeofday(&endTime, NULL);

    // Convert the times to seconds
    double initialTime = startTime.tv_sec+(startTime.tv_usec/1000000.0);
    double finalTime = endTime.tv_sec+(endTime.tv_usec/1000000.0);

    // Calculate and display the duration
    cout << finalTime - initialTime << " seconds elapsed to process "
        << NUM_CYCLES << " cycles." << endl;
}
