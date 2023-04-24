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

    void EnterQ(Time);
    Time LeaveQ(Time);
    int getID() { return _id; }
    bool operator<(const Message& m) const { return _id > m._id; }
    void setDestination(Computer* computer);
    Computer* getSource() const;
    Computer* getDestination() const;
    void setEnd(Time end) { _destinationTime = end; }
    Time getCommTime() { return _destinationTime - _creationTime; }
    Time getWaitTime() { return _waitTime; }
private:
    Computer* _source;
    Computer* _destination;
    int _id;
    //static int NextID;
    Time _creationTime;
    Time _destinationTime;
    Time _waitTime,_enterQ,_exitQ,_totalTime;

	int _timesStopped; // number of wait times
};
