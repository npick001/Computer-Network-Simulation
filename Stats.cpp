#include "Stats.h"

StatContainer::StatContainer()
{
    _start = SimulationExecutive::GetSimulationTime();
    _timesStopped = 0;
    _QueueT = 0;
}

void StatContainer::EnterQ(Time Eq)
{
    _enterQ = Eq;
}

void StatContainer::LeaveQ(Time Lq)
{
    _exitQ = Lq;
    _QueueT += (_exitQ - _enterQ);
    _timesStopped++;
}
