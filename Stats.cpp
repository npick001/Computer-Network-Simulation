#include "Stats.h"

StatContainer::StatContainer()
{
    _start = SimulationExecutive::GetSimulationTime();
}

void StatContainer::EnterN(Time en)
{
    _enterN = en;
}

void StatContainer::LeaveN(Time ln)
{
    _exitN = ln;
}

void StatContainer::EnterQ(Time Eq)
{
    _enterQ = Eq;
}

void StatContainer::LeaveQ(Time Lq)
{
    _exitQ = Lq;
    _QueueT += (_exitQ - _enterQ);
}
