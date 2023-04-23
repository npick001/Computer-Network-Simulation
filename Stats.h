#pragma once
#include <list>
#include "SimulationExecutive.h"

class StatContainer
{
public:
    StatContainer();
    void EnterN(Time En);
    void LeaveN(Time Ln);
    void EnterQ(Time Eq);
    void LeaveQ(Time Lq);

private:
    Time _start, _end, _enterN, _enterQ, _exitN, _exitQ;
    std::list<Time> _TinNode;
    Time _QueueT;
};