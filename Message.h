#pragma once
#include "SimulationExecutive.h"
#include <iostream>

class Computer; // Forward declaration

class Message
{
public:
    Message(Computer* source, Computer* destination, Time creationTime);
    ~Message();

    void updateWaitTime(Time waitTime);
    void reportStatistics() const;

    Computer* getSource() const;
    Computer* getDestination() const;

private:
    Computer* _source;
    Computer* _destination;

    Time _creationTime;
    Time _destinationTime;
    Time _waitTime;

    int _timesStopped; // number of wait times
};
