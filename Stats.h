#pragma once
#include <list>
#include "SimulationExecutive.h"
#include "Computer.h"

class Computer;
class Message;
class StatsHolder
{
public:
	StatsHolder(){}
	void addPC(Computer* c)
	{
		PCList.push_back(c);
	}
	void addMSG(Message* m)
	{
		MSGList.push_back(m);
	}
	void ReportStats();
private:
	std::list<Computer*> PCList;
	std::list<Computer*>::iterator PCItr;
	std::list<Message*> MSGList;
	std::list<Message*>::iterator MSGItr;
};