#include "SimulationExecutive.h"

SimulationExecutive* SimulationExecutive::_instance = 0;

SimulationExecutive::SimulationExecutive() 
{
	_es = new EventSet();
	_simTime = 0;
}

Time SimulationExecutive::GetSimulationTime()
{
	return _simTime;
}

SimulationExecutive* SimulationExecutive::GetInstance()
{
	if (_instance == 0) {
		_instance = new SimulationExecutive();
	}

	return _instance;
}

void SimulationExecutive::RunSimulation()
{
	_simTime = 0;

	while (!_es->IsEmpty()) {

		Time executeTime = _es->GetMinTime();
		EventAction* ea = _es->GetEvent();

		_simTime = executeTime;
		ea->Execute();
	}
}

void SimulationExecutive::RunSimulation(Time endTime)
{
	_simTime = 0;

	while (!_es->IsEmpty() && _es->GetMinTime() <= endTime) {

		Time executeTime = _es->GetMinTime();
		EventAction* ea = _es->GetEvent();

		_simTime = executeTime;
		ea->Execute();
	}
}

void SimulationExecutive::SchedEventAt(Time t, EventAction* ea)
{
	_es->AddEvent(t, ea);
}

void SimulationExecutive::SchedEventIn(Time delta, EventAction* ea)
{
	_es->AddEvent(_simTime + delta, ea);
}