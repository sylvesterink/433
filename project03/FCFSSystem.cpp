#include "FCFSSystem.h"

FCFSSystem::FCFSSystem()
{
    CPU = NULL;
}

FCFSSystem::~FCFSSystem()
{
    cleanupProcesses();
}


void FCFSSystem::onProcArrival(int PID)
{
    cout << "Process Arrived " << PID << endl;
}

void FCFSSystem::onCpuComplete(int PID)
{
    cout << "Burst Complete " << PID << endl;
}

void FCFSSystem::onIoComplete(int PID)
{
    cout << "IO Complete " << PID << endl;
}

void FCFSSystem::onTimerExpiration(int PID)
{
    cout << "Timer Expired " << PID << endl;
}

void FCFSSystem::dispatch()
{

}

void FCFSSystem::cleanupProcesses()
{
    for (unsigned int i = 0; i < processList.size(); i++) {
        if (processList[i] != NULL) {
            delete processList[i];
            processList[i] = NULL;
        }
    }
}
