#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sys/time.h>

using namespace std;

#include "PCB.h"
#include "ReadyQueue.h"

static const int TABLE_SIZE = 20;
static const int MAX_PRIORITY = 50;
static const int NUM_CYCLES = 1000000;

void initialize(PCB*);
void partOne(PCB*);
void partTwo(PCB*);

int main(int argc, const char *argv[])
{
    PCB* PCB_table;

    cout << "Priority Queue" << endl;
    cout << "Cavan Crawford and Brandon Kasa" << endl;

    cout << "Test 1:" << endl;
    PCB_table = new PCB[TABLE_SIZE];
    initialize(PCB_table);
    srand(time(0)); //initialize random number generator
    partOne(PCB_table);
    delete[] PCB_table;

    cout << "\n\nTest 2:" << endl;
    PCB_table = new PCB[TABLE_SIZE];
    initialize(PCB_table);
    srand(time(0)); //initialize random number generator
    partTwo(PCB_table);
    delete[] PCB_table;

    return 0;
}

void initialize(PCB* table)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].id = i + 1;
        table[i].priority = i + 1;
        table[i].state = WAITING;
    }
}

void partOne(PCB* table)
{
    ReadyQueue q1;
    q1.insertProc(&table[4]);
    q1.insertProc(&table[0]);
    q1.insertProc(&table[7]);
    q1.insertProc(&table[10]);

    q1.displayQueue();
    q1.removeHighestProc();
    q1.displayQueue();

    q1.insertProc(&table[2]);
    q1.insertProc(&table[6]);
    q1.insertProc(&table[1]);
    q1.insertProc(&table[11]);
    q1.insertProc(&table[8]);

    while (!q1.isEmpty()) {
        q1.removeHighestProc();
        q1.displayQueue();
    }
}

void partTwo(PCB* table)
{
    ReadyQueue q1;
    int random = 0;

    for(int i = 0; i < 10; i++) {
        random = (rand() % TABLE_SIZE);
        while (table[random].state == READY) {
            random= (random + 1) % TABLE_SIZE;
        }

        table[random].priority = (rand() % MAX_PRIORITY) + 1;
        q1.insertProc(&table[random]);
    }

    timeval endTime;
    timeval startTime;

    gettimeofday(&startTime, NULL);

    int i;
    for(i = 0; i < NUM_CYCLES; i++) {
        //q1.removeHighestProc();
        cout << q1.removeHighestProc().id << endl;
        q1.displayQueue();

        q1.agePriority();

        random = (rand() % TABLE_SIZE);
        while (table[random].state == READY) {
            random= (random + 1) % TABLE_SIZE;
        }

        table[random].priority = (rand() % MAX_PRIORITY) + 1;
        q1.insertProc(&table[random]);
    }

    cout << i << endl;
    unsigned long initialTime = (startTime.tv_sec * NUM_CYCLES) + (startTime.tv_usec);
    unsigned long finalTime = (endTime.tv_sec * NUM_CYCLES) + (endTime.tv_usec);

    cout << finalTime - initialTime << " microseconds elapsed" << endl;
}
