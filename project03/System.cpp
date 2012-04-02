/**
 * @file System.cpp
 * @brief The implementation of the system abstract object.
 *        All other simulation systems are derived from this for simplicity
 * @author Cavan Crawford & Brandon Kasa
 * @version 1.0
 * @date 2012-04-02
 */
#include "System.h"

/**
 * @brief Constructor
 */
System::System()
{
    CPU = NULL;
}

/**
 * @brief Destructor
 */
System::~System()
{

}

/**
 * @brief Initializes the process list and creates an arrival event for each
 *        added process
 * @param numProcesses Number of processes to simulate
 */
void System::initializeProcesses(int numProcesses)
{
    for (int i = 0; i < numProcesses; i++) {
        Process* newProcess = new Process(i);
        processList.push_back(newProcess);

        Event newEvent(E_PROCESS_ARRIVAL, newProcess->getStartTime(), i);
        eventQueue.push(newEvent);
    }

}

/**
 * @brief Runs the simulation of the process handling each event in the event
 *        queue
 * @param numProcesses Number of processes to simulate
 * @param maxTime Maximum time for simulation to run
 */
void System::simulation(int numProcesses, int maxTime)
{
    // Create processes and add initial events
    initializeProcesses(numProcesses);

    int currentTime = 0;
    _maxTime = maxTime;

    // While there are events and time isn't complete, handle the events.
    while ( (!eventQueue.empty()) && (currentTime < maxTime) ) {
        Event nextEvent = eventQueue.top();
        eventQueue.pop();
        currentTime = nextEvent.getStartTime();
        handleEvent(nextEvent);
    }

    // Print the final statistics
    reportStatistics();

    // Clean up processes
    cleanupProcesses();
}

/**
 * @brief Depending on the event type, call the appropriate event handler
 *        The event handlers are implemented in the derived class
 * @param event Event to be handled
 */
void System::handleEvent(Event &event)
{
    int eventType = event.getType();

    switch (eventType) {
        case E_PROCESS_ARRIVAL:
            onProcArrival(event);
            break;
        case E_CPU_BURST_COMPLETION:
            onCpuComplete(event);
            break;
        case E_IO_COMPLETION:
            onIoComplete(event);
            break;
        case E_TIMER_EXPIRATION:
            onTimerExpiration(event);
            break;
    }
}

/**
 * @brief Output the statistics of the simulation
 */
void System::reportStatistics()
{
    cout << "Statistics" << endl;

    // Output the statistics for individual processes
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

    // Output statistics of overall system simulation
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

/**
 * @brief Deallocate memory for processes
 */
void System::cleanupProcesses()
{
    for (unsigned int i = 0; i < processList.size(); i++) {
        if (processList[i] != NULL) {
            delete processList[i];
            processList[i] = NULL;
        }
    }
}

/**
 * @brief A dummy implementation of the timer expiration event
 *        This is implemented here so that it isn't necessary to derive in all
 *        child classes, as only RR uses it currently.
 *        However, it needs to exist since the event handler calls it.
 *        This can be fixed by modifying the event handler in the derived class
 * @param event Event to handle
 */
void System::onTimerExpiration(Event &event)
{
    //Dummy Function
}
