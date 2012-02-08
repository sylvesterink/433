#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

#include "PCB.h"
#include "ReadyQueue.h"

static const int TABLE_SIZE = 20;

void initialize(PCB*);
void partOne(PCB*);
void partTwo(PCB*);

int main(int argc, const char *argv[])
{
    PCB* PCB_table;

    cout << "Priority Queue" << endl;
    cout << "Cavan Crawford and Brandon Kasa" << endl;

    //cout << "Test 1:" << endl;
    //PCB_table = new PCB[TABLE_SIZE];
    //initialize(PCB_table);
    //srand(time(0)); //initialize random number generator
    //partOne(PCB_table);
    //delete[] PCB_table;

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
        table[i].setId(i + 1);
        table[i].setPriority(i + 1);
        table[i].setState(WAITING);
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

    q1.insertProc(&table[3]);
    q1.displayQueue();
    //ReadyQueue q1;
    //int r;
    //for(int i = 0; i < 10; i++) {
        //r = (rand() % 50) + 1;
        //if(table
                //q1.insertProc()
                //}
}
