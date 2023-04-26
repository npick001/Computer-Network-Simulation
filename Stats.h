#pragma once
#include <list>
#include "SimulationExecutive.h"
#include "Computer.h"
#include <iostream>

class Computer;			//Forward Declarations
class Message;

class StatsHolder		//Container that stores objects for analysis and output
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
	void ReportStats();						//Display Fn
private:
	std::list<Computer*> PCList;			//List of computers to be reported
	std::list<Computer*>::iterator PCItr;
	std::list<Message*> MSGList;			//List of messages to be reported
	std::list<Message*>::iterator MSGItr;
};