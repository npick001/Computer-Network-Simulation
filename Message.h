#pragma once
#include "Computer.h"
#include "SimulationExecutive.h"
#include <iostream>

class Message
{
public:
	Message();
	~Message();
	void ReportStatistics();
	void EnterQ(Time Eq);
	void LeaveQ(Time Lq);
private:
//	Computer* _source;
//	Computer* _destination;

	Time _creationTime;
	Time _destinationTime;
	Time _waitTime;
	int _timesStopped; // number of wait times
};

