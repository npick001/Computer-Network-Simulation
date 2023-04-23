#pragma once
#include <list>
#include "SimulationExecutive.h"

class StatContainer
{
public:
    StatContainer();
    void EnterQ(Time Eq);
    Time LeaveQ(Time Lq);

private:
    Time _start, _end, _enterQ, _exitQ;     // Start/End Times
    Time _enterQ, _exitQ, _QueueT;          // Queue arrival/departure times, and total queue time
    int _timesStopped;                      // number of wait times
};


class MsgStatSorter
{
public:
    MsgStatSorter(int ID, StatContainer sc)
    {
        _id = ID;
        _stats = sc;
    }
    int GetID() { return _id; }
    StatContainer GetStatContainer() { return _stats}
private:
    int _id;
    StatContainer _stats;
};

std::list<MsgStatSorter> StatSet;
std::list<MsgStatSorter>::iterator StatItr;
std::list<Computer*> ComputerSet;