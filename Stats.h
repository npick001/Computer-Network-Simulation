#pragma once
#include <list>
#include "SimulationExecutive.h"

class StatContainer
{
public:
    StatContainer();
    void EnterQ(Time Eq);
    void LeaveQ(Time Lq);

private:
    Time _start, _end, _enterQ, _exitQ;     // Start/End Times
    Time _enterQ, _exitQ, _QueueT;          // Queue arrival/departure times, and total queue time
    int _timesStopped;                      // number of wait times
};


class StatSorter
{
public:
    StatSorter(int ID, StatContainer _sc);
    int GetID() { return _id; }
    StatContainer GetStatContainer() { return _stats}
private:
    int _id;
    StatContainer _stats;
};

std::list<StatSorter> StatSet;
std::list<StatSorter>::iterator StatItr;