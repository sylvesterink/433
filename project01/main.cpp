#include <iostream>

using namespace std;

#include "PCB.h"
#include "ReadyQueue.h"

static const int TABLE_SIZE = 20;

void initializeTable(PCB*);
void partOne();
void partTwo();

int main(int argc, const char *argv[])
{
    PCB PCB_table[TABLE_SIZE];

    cout << PCB_table[0].getId() << endl;
    cout << PCB_table[0].getPriority() << endl;
    cout << PCB_table[0].getState() << endl;

    return 0;
}

void initializeTable(PCB*)
{

}

void partOne()
{

}

void partTwo()
{

}
