#include <iostream>
#include "SimulationExecutive.h"

using namespace std;


struct Event
{
	Event(Time time, EventAction* ea)
	{
		_time = time;
		_ea = ea;
		_nextEvent = NULL;
	}
	Time _time;
	EventAction* _ea;
	Event* _nextEvent;
};



class SimulationExecutive
{
public:
	static void InitializeSimulation()
	{
		_simTime = 0.0;
	}

	static Time GetSimulationTime() { return _simTime; }
	static void RunSimulation()
	{
		while (_eventList.HasEvent()) {
			Event* e = _eventList.GetEvent();
			_simTime = e->_time;
			e->_ea->Execute();
			delete e;
		}
	}

	static void RunSimulation(Time endTime)
	{
		while (_eventList.HasEvent() && _simTime <= endTime) {
			Event* e = _eventList.GetEvent();
			_simTime = e->_time;
			if (_simTime <= endTime) {
				e->_ea->Execute();
			}
			delete e;
		}
	}

	static void ScheduleEventIn(Time delta, EventAction* ea)
	{
		_eventList.AddEvent(_simTime + delta, ea);
	}

	static void ScheduleEventAt(Time time, EventAction* ea)
	{
		_eventList.AddEvent(time, ea);
	}


private:

	class EventList
	{
	public:
		EventList()
		{
			_eventList = 0;
		}

		void AddEvent(Time time, EventAction* ea)
		{
			Event* em = new Event(time, ea);
			if (_eventList == 0) {
				//event list empty
				_eventList = em;
			}
			else if (time < _eventList->_time) {
				//goes at the head of the list
				em->_nextEvent = _eventList;
				_eventList = em;
			}
			else {
				//search for where to put the event
				Event* curr = _eventList;

				while ((curr->_nextEvent != 0) ? (em->_time >= curr->_nextEvent->_time) : false) {
					curr = curr->_nextEvent;
				}
				if (curr->_nextEvent == 0) {
					//goes at the end of the list
					curr->_nextEvent = em;
				}
				else {
					em->_nextEvent = curr->_nextEvent;
					curr->_nextEvent = em;
				}
			}
		}


		Event* GetEvent()
		{
			Event* next = _eventList;
			_eventList = _eventList->_nextEvent;
			return next;
		}
		bool HasEvent()
		{
			return _eventList != 0;
		}
		void PrintEventList()
		{
			Event* e = _eventList;
			cout << "     EventList: " << endl;;
			while (e != NULL) {
				cout << "          " << e << ", " << e->_time << ", " << e->_ea << ", " << endl;
				e = e->_nextEvent;
			}
		}
	private:
		Event* _eventList;


	};

	static EventList _eventList;
	static Time _simTime;
};

SimulationExecutive::EventList SimulationExecutive::_eventList;
Time SimulationExecutive::_simTime = 0.0;

void InitializeSimulation()
{
	SimulationExecutive::InitializeSimulation();
}

Time GetSimulationTime()
{
	return SimulationExecutive::GetSimulationTime();
}

void RunSimulation()
{
	SimulationExecutive::RunSimulation();
}

void RunSimulation(Time endTime)
{
	SimulationExecutive::RunSimulation(endTime);
}

void ScheduleEventIn(Time delta, EventAction* ea)
{
	SimulationExecutive::ScheduleEventIn(delta, ea);
}

void ScheduleEventAt(Time time, EventAction* ea)
{
	SimulationExecutive::ScheduleEventAt(time, ea);
}

