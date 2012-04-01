#include "System.h"

System::System()
{
    CPU = NULL;
}

System::~System()
{

}

void System::initializeProcesses(int numProcesses)
{
    for (int i = 0; i < numProcesses; i++) {
        Process* newProcess = new Process(i);
        processList.push_back(newProcess);

        Event newEvent(E_PROCESS_ARRIVAL, newProcess->getStartTime(), i);
        eventQueue.push(newEvent);
    }

}

//TODO: Move into System object
void System::simulation(int numProcesses, int maxTime)
{
    initializeProcesses(numProcesses);

    int currentTime = 0;
    _maxTime = maxTime;

    while ( (!eventQueue.empty()) && (currentTime < maxTime) ) {
        Event nextEvent = eventQueue.top();
        eventQueue.pop();
        currentTime = nextEvent.getStartTime();
        handleEvent(nextEvent);
    }

    reportStatistics();

    cleanupProcesses();
}

void System::handleEvent(Event &event)
{
    int eventType = event.getType();

    switch (eventType) {
        case E_PROCESS_ARRIVAL:
            onProcArrival(event);
            //handle_proc_arrival(e)
            break;
        case E_CPU_BURST_COMPLETION:
            onCpuComplete(event);
            //handle_CPU_completion(e)
            break;
        case E_IO_COMPLETION:
            onIoComplete(event);
            //handle_IO_completion(e)
            break;
        case E_TIMER_EXPIRATION:
            onTimerExpiration(event);
            //handle_Timer_expiration(e)
            break;
    }

    //schedular.run();
}

void System::reportStatistics()
{
    cout << "Statistics" << endl;

    int listSize = processList.size();
    int cpuUtilization = 0;
    int completedJobs = 0;
    int totalTurnaroundTime = 0;
    for (int i = 0; i < listSize; i++) {
        cout << "Process " << i << ":" << endl;

        cout << "arrival time: " << processList[i]->getStartTime() << endl;
        cout << "finish time: " << processList[i]->getCompletedTime() << endl;
        cout << "service time: " << processList[i]->getServiceTime() << endl;
        cout << "I/O time: " << processList[i]->getIoTime() << endl;

        long waitingTime = _maxTime;
        cout << "turnaround time: ";
        if (processList[i]->getCompletedTime() > 0) {
            long turnaroundTime = processList[i]->getCompletedTime()
                                - processList[i]->getStartTime();
            cout << turnaroundTime << endl;
            waitingTime = turnaroundTime - processList[i]->getServiceTime()
                        - processList[i]->getIoTime();

            completedJobs++;
            totalTurnaroundTime += turnaroundTime;
        }
        else {
            cout << "NA" << endl;

            waitingTime -= processList[i]->getStartTime()
                        - processList[i]->getServiceTime()
                        - processList[i]->getIoTime();
        }

        cout << "waiting time: " << waitingTime << "\n";
        cout << endl;

        cpuUtilization += processList[i]->getServiceTime();
    }

    cout << "________________________" << endl;
    float cpuUtilizationP = ( float(cpuUtilization) / float(_maxTime) ) * 100;
    cout << "CPU Utilization: " << cpuUtilizationP << "%" << endl;
    float throughput = ( float(completedJobs) / float(listSize) )
                        / ( float(_maxTime) / 1000 );
    cout << "Throughput is " << throughput << " jobs / s" << endl;

    if (completedJobs != 0) {
        float avgTurnaround = float(totalTurnaroundTime) / float(completedJobs)
                        / ( float(_maxTime) / 1000 );
        cout << "Average turnaround time: " << avgTurnaround << " s" << endl;
    }
    else {
        cout << "Average turnaround time: NA" << endl;
    }

    cout << "\n" << endl;
}

void System::cleanupProcesses()
{
    for (unsigned int i = 0; i < processList.size(); i++) {
        if (processList[i] != NULL) {
            delete processList[i];
            processList[i] = NULL;
        }
    }
}

void System::onTimerExpiration(Event &event)
{
    //Dummy Function
}
