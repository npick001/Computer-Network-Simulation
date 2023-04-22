#include "Stats.h"

StatContainer::StatContainer()
{
    _start = SimulationExecutive::GetSimulationTime();
}

void StatContainer::EnterN()
{
    _enterN = SimulationExecutive::GetSimulationTime();
}

void StatContainer::LeaveN()
{
    _exitN = SimulationExecutive::GetSimulationTime();
}
