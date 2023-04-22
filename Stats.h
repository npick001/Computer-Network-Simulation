#pragma once
#include <list>
#include "SimulationExecutive.h"

class StatContainer
{
public:
    StatContainer();
    void EnterN();
    void LeaveN();

private:
    Time _start, _end, _enterN, _exitN;
    std::list<Time> _TinNode;
    std::list<Time> _QueueT;
};