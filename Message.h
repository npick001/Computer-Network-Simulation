#pragma once
<<<<<<< HEAD
#include "Stats.h"
#include "Computer.h"
#include "SimulationExecutive.h"
class Computer;
class Message
{
public:
	Message(Computer* source, Computer* destination);
	~Message();
	void ReportStatistics();
=======
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

>>>>>>> pepper2.0
private:
    Computer* _source;
    Computer* _destination;

    Time _creationTime;
    Time _destinationTime;
    Time _waitTime;

<<<<<<< HEAD
	StatContainer* _stats;
	int _timesStopped; // number of wait times
=======
    int _timesStopped; // number of wait times
>>>>>>> pepper2.0
};
