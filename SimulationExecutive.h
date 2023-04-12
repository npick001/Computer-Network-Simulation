#pragma once
typedef double Time;
#include "EventSet.h"
class EventSet;

class EventAction
{
public:
	EventAction() {};
	virtual void Execute() = 0;
};

/**************************************************/
/* Singleton Simulation Executive */
/**************************************************/
class SimulationExecutive {
public:
	static SimulationExecutive* GetInstance();

	void RunSimulation();
	void RunSimulation(Time endTime);
	void SchedEventAt(Time t, EventAction* ea);
	void SchedEventIn(Time delta, EventAction* ea);
	Time GetSimulationTime();
private:
	SimulationExecutive();
	EventSet* _es;
	Time _simTime;
	static SimulationExecutive* _instance;
};


