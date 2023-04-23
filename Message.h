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

    void updateWaitTime(Time waitTime);
    void reportStatistics() const;

    void setDestination(Computer* computer);
    Computer* getSource() const;
    Computer* getDestination() const;
private:
    Computer* _source;
    Computer* _destination;

    Time _creationTime;
    Time _destinationTime;
    Time _waitTime;

	StatContainer* _stats;
	int _timesStopped; // number of wait times
};
