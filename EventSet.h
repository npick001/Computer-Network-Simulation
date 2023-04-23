#pragma once
#include <iostream>
#include "SimulationExecutive.h"
class EventAction;

#define GEN_OUTPUT 0

class EventSet {

public:
	EventSet() {
		_head = 0;
		_size = 0;
	}

	/*
		This function uses an insertion sort to add the event
		at the position in ascending order.

		This is so the removal of an event occurs at the head.
	*/
	void AddEvent(Time t, EventAction* ea);

	/*
		This function returns the event with the
		lowest time stamp.
	*/
	EventAction* GetEvent();

	/*
		This is a debugging function
		designed to print out the times in the event set.
	*/
	void PrintEventSet();

	/*
		This function returns the event time
		of the first event in the list -> already sorted
	*/
	Time GetMinTime();
	bool IsEmpty();

private:

	struct Node {
		Node(Time t, EventAction* ea) {
			_ea = ea;
			_eventTime = t;
			_next = 0;
		}
		EventAction* _ea;
		Time _eventTime;
		Node* _next;
	};

	Node* _head;
	int _size;
};
