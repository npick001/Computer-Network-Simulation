#pragma once
#include "Stats.h"
#include "Computer.h"
#include "SimulationExecutive.h"

class Message
{
public:
	Message(Computer* source, Computer* destination);
	~Message();
	void ReportStatistics();
private:
	Computer* _source;
	Computer* _destination;

	Time _creationTime;
	Time _destinationTime;
	Time _waitTime;

	StatContainer* _stats;
	int _timesStopped; // number of wait times
};

