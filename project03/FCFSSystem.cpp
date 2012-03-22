#include "FCFSSystem.h"

FCFSSystem::FCFSSystem()
{
    CPU = NULL;
}

FCFSSystem::~FCFSSystem()
{
    cleanupProcesses();
}


void FCFSSystem::onProcArrival(Event &event)
{
    cout << "Process Arrived " << event.getPID() << endl;
}

void FCFSSystem::onCpuComplete(Event &event)
{
    cout << "Burst Complete " << event.getPID() << endl;
}

void FCFSSystem::onIoComplete(Event &event)
{
    cout << "IO Complete " << event.getPID() << endl;
}

void FCFSSystem::onTimerExpiration(Event &event)
{
    cout << "Timer Expired " << event.getPID() << endl;
}

void FCFSSystem::dispatch()
{

}

