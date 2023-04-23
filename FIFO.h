#pragma once
#include <iostream>
#include "SimulationExecutive.h"
#include "Stats.h"
/**************************

FIFO Queue, with added functionality.

***************************/
template <class T>
class FIFO
{
public:
	FIFO(std::string name)
	{
		_head = 0;
		_tail = 0;
		_size = 0;
		_name = name;
		totalMsg = 0;
		WaitTimes = 0;
		maxSize = 0;
	}

	void AddEntity(T* t)
	{
		Node* node = new Node(t);
		if (_head == 0) {	//empty list
			_head = _tail = node;
		}
		else {
			_tail = _tail->next = node;
		}
		((Message*)t)->EnterQ(SimulationExecutive::GetSimulationTime()); // Marks the time a message joined the queue;

	//	std::cout << GetSimulationTime() << ", queue " << _name << ", AddEntity, Entity , queue size, " << _size << std::endl;
		_size++;
		totalMsg++;
		if (_size > maxSize) maxSize = _size;
	//	std::cout << GetSimulationTime() << ", queue " << _name << ", AddEntity, Entity , queue size, " << _size << std::endl;
	}

	T* GetEntity()
	{
		if (_head == 0) return 0;
		else {
			Node* n = _head;
			T* t = _head->t;
			_head = _head->next;
			//			delete n;
//			std::cout << GetSimulationTime() << ", queue " << _name << ", GetEntity, Entity , queue size, " << _size << std::endl;
			_size--;
		//	std::cout << GetSimulationTime() << ", queue " << _name << ", GetEntity, Entity , queue size, " << _size << std::endl;
			WaitTimes += ((Message*)t)->LeaveQ(SimulationExecutive::GetSimulationTime());
			return t;
		}
	}

	T* ViewEntity()
	{
		return(_head->t);
	}

	bool IsEmpty() { return (_size == 0); }
	int GetSize() { return _size; }
private:
	struct Node
	{
		Node(T* t) {
			this->t = t;
			next = 0;
		}
		T* t;
		Node* next;
	};

	int totalMsg, maxSize;
	Time WaitTimes;
	Node* _head;
	Node* _tail;
	int _size;
	std::string _name;
};
