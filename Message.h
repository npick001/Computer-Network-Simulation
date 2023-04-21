#pragma once
#include "Computer.h"

class Message
{
public:
	Message();
	~Message();
	void ReportStatistics();
private:
	Computer* _source;
	Computer* _destination;

	Time _creationTime;
	Time _destinationTime;
	Time _waitTime;

	int _timesStopped; // number of wait times
};

