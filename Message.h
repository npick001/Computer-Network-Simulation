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
	Time LeaveQ(Time Lq);
private:
//	Computer* _source;
//	Computer* _destination;
	int _id;
	static int nextID;
	StatContainer _sc;
};

