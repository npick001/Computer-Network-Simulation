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

void StatContainer::EnterQ()
{
    _enterQ = SimulationExecutive::GetSimulationTime();
}

void StatContainer::LeaveQ()
{
    _exitQ = SimulationExecutive::GetSimulationTime();
}