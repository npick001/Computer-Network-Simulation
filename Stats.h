#pragma once
#include <list>
#include "SimulationExecutive.h"

class StatContainer
{
public:
	StatContainer();
	void EnterN();
	void LeaveN();
	void EnterQ();
	void LeaveQ();

private:
	Time _start, _end, _enterQ, _exitQ;
	std::list<Time> _TinNode;
	std::list<Time> _QueueT;
};