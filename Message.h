#pragma once

#include "Stats.h"
#include "Computer.h"
#include "SimulationExecutive.h"
#include <iostream>

class Computer;
class Message
{
public:
    Message(Computer* source, Computer* destination, Time creationTime);
    ~Message();
    void ComputeStats();
    void EnterQ(Time E);
    Time LeaveQ(Time L);
    void ReachEnd();
    bool operator<(const Message& m) const;
    void setDestination(Computer* computer);
    Computer* getSource() const;
    Computer* getDestination() const;
private:
    Computer* _source;
    Computer* _destination;
    Time _start, _end;                      // Start/End Times
    Time _enterQ, _exitQ, _QueueT;          // Queue arrival/departure times, and total queue time
    int _timesStopped,ID;                      // number of wait times
    static int nextID;
    Time avgWait;
    Time commsTime;
};
