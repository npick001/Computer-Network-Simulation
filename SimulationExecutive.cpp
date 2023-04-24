#include <iostream>
#include "SimulationExecutive.h"

using namespace std;

struct SimulationExecutive::Event
{
	Event(Time time, EventAction* ea)
	{
		_time = time;
		_ea = ea;
		_nextEvent = 0;
	}
	Time _time;
	EventAction* _ea;
	Event* _nextEvent;
};

class SimulationExecutive::EventSet
{
public:
	EventSet()
	{
		_numBins = 10;
		_deltaT = 0.25;
		_calQueue = new EventList * [_numBins];

		// instantiate a number of lists and save in a single array
		for (int i = 0; i < _numBins; i++) {
			_calQueue[i] = new EventList();
		}
	}

	void AddEvent(Time time, EventAction* ea)
	{
		int index = GetIndex(time);
		_calQueue[index]->AddEvent(time, ea);
	}

	// this function assumes that the set has an event
	Time GetTime()
	{
		int index = GetIndex(_simTime);

		// check all bins if they have an event, starting at this bin
		for (int i = index; i < _numBins + index; i++) {
			i = i % _numBins;
			if (_calQueue[i]->HasEvent()) {
				index = i;
				break;
			}
		}
		return _calQueue[index]->GetMinTime();
	}

	// this function assumes the set has an event
	EventAction* GetEventAction()
	{
		int index = GetIndex(GetTime());
		return _calQueue[index]->GetEventEA();
	}

	bool HasEvent()
	{
		// loop thru each list and see if any of them have an event
		// if they do have an event, then break out.
		// if none of them return true, then there are no events in the whole list.
		for (int i = 0; i < _numBins; i++) {
			if (_calQueue[i]->HasEvent()) {
				return true;
				break;
			}
		}
		return false;
	}

	// function for testing different bin sizes through the batch file.
	void SetDeltaT(Time t) {
		_deltaT = t;
	}

	// function for testing different number of bins through batch file
	void SetNumBins(int numBins) {
		for (int i = 0; i < _numBins; i++) {
			delete _calQueue[i];
		}
		_numBins = numBins;

		// after changing number of bins, delete set and create new.
		delete[] _calQueue;
		_calQueue = new EventList * [_numBins];

		// instantiate a number of lists and save in a single array
		for (int i = 0; i < _numBins; i++) {
			_calQueue[i] = new EventList();
		}
	}

	// DEBUGGING FUNCTION
	void PrintEventLists() {
		for (int i = 0; i < _numBins; i++) {
			if (_calQueue[i]->HasEvent()) {
				std::cout << "Printing Index:" << i << std::endl << std::endl;
				_calQueue[i]->PrintEventList();
				std::cout << std::endl << std::endl;
			}
		}
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
			Event* e = new Event(time, ea);
			if (_eventList == 0) {
				//event list empty
				_eventList = e;
			}
			else if (time < _eventList->_time) {
				//goes at the head of the list
				e->_nextEvent = _eventList;
				_eventList = e;
			}
			else {
				//search for where to put the event
				Event* curr = _eventList;
				while ((curr->_nextEvent != 0) ? (e->_time >= curr->_nextEvent->_time) : false) {
					curr = curr->_nextEvent;
				}
				if (curr->_nextEvent == 0) {
					//goes at the end of the list
					curr->_nextEvent = e;
				}
				else {
					e->_nextEvent = curr->_nextEvent;
					curr->_nextEvent = e;
				}
			}
		}

		Time GetMinTime() {
			return _eventList->_time;
		}

		EventAction* GetEventEA()
		{
			Event* next = _eventList;
			_eventList = _eventList->_nextEvent;
			return next->_ea;
		}

		bool HasEvent()
		{
			return _eventList != 0;
		}

		// THIS NEEDS TO REMAIN PRIVATE FOR SUBMISSIONS
		void PrintEventList()
		{
			Event* e = _eventList;
			cout << "     EventList: " << endl;;
			while (e != NULL) {
				cout << "          " << e << ", " << e->_time << ", " << e->_ea << endl;
				e = e->_nextEvent;
			}
		}
	private:
		Event* _eventList;
	};

	int GetIndex(Time t) {
		return ((int)(t / _deltaT) % _numBins);
	}

	int _numBins;
	double _deltaT;
	EventList** _calQueue;
};

SimulationExecutive::EventSet SimulationExecutive::_eventSet;
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

void ScheduleEventIn(Time delta, EventAction*ea)
{
	SimulationExecutive::ScheduleEventIn(delta, ea);
}

void ScheduleEventAt(Time time, EventAction*ea)
{
	SimulationExecutive::ScheduleEventAt(time, ea);
}


