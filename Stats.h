#pragma once
#include <list>
#include "SimulationExecutive.h"
#include "Computer.h"
#include <iostream>

class Computer;
class Message;
class StatsHolder
{
public:
	StatsHolder(){}

	Computer* addPC(Computer* c)
	{
		PCList.push_back(c);
		return c;
	}
	Message* addMSG(Message* m)
	{
		MSGList.push_back(m);
		return m;
	}
	void ReportStats();
private:
	std::list<Computer*> PCList;
	std::list<Computer*>::iterator PCItr;
	std::list<Message*> MSGList;
	std::list<Message*>::iterator MSGItr;
};