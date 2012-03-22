#include "System.h"

System::System()
{

}

System::~System()
{

}

void System::handleEvent(Event &e)
{
    int eventType = e.getType();

    switch (eventType) {
        case E_PROCESS_ARRIVAL:
            onProcArrival(e.getPID());
            //handle_proc_arrival(e)
            break;
        case E_CPU_BURST_COMPLETION:
            onCpuComplete(e.getPID());
            //handle_CPU_completion(e)
            break;
        case E_IO_COMPLETION:
            onIoComplete(e.getPID());
            //handle_IO_completion(e)
            break;
        case E_TIMER_EXPIRATION:
            onTimerExpiration(e.getPID());
            //handle_Timer_expiration(e)
            break;
    }

    //schedular.run();
}
