#include "EventSet.h"

void EventSet::AddEvent(Time t, EventAction* ea) {

	/*
		check nodes and do an insertion sort
		to insert event in the correct position
		between the correct time steps.
	*/

	Node* node = new Node(t, ea);

	if (_head == 0) {
		_head = node;
	}
	else {
		Node* current = _head;

		// check if it is smaller than the head
		if (node->_eventTime < _head->_eventTime) {
			node->_next = _head;
			_head = node;
		}
		else {

			// check all nodes in event set except head
			// for conditional insertion
			while (current->_next != NULL && current->_next->_eventTime < node->_eventTime) {
				current = current->_next;
			}

			// add the node in the correct position
			node->_next = current->_next;

			// move the list to after the insertion
			current->_next = node;
		}
	}
	_size++;
#if GEN_OUTPUT
	std::cout << "Size: " << _size << std::endl;
	PrintEventSet();
#endif // GEN_OUTPUT
}

EventAction* EventSet::GetEvent() {

	if (_head == 0) return 0;
	else {
		// save the EA from the head
		EventAction* ea = _head->_ea;
		Node* n = _head;
		_head = _head->_next;

#if GEN_OUTPUT
		PrintEventSet();
		std::cout << "Size: " << _size << std::endl;
#endif // GEN_OUTPUT

		// remove the event from list
		delete n;
		_size--;
		return ea;
	}
}

void EventSet::PrintEventSet() {

	Node* current = _head;
	int eventNumber = 1;

	std::cout << "Event set size: " << _size << std::endl;
	while (current != NULL) {
		std::cout << "Position " << eventNumber << " execution time is: " << current->_eventTime << std::endl;
		current = current->_next;
		eventNumber++;
	}
}


Time EventSet::GetMinTime() {
	return(_head->_eventTime);
}

bool EventSet::IsEmpty() {
	return(_size == 0);
}
