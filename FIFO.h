#pragma once
#include <iostream>
#include "SimulationExecutive.h"
#include "Message.h"

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
		totalQ = 0;
		max = 0;
		count = 0;
		avgsize = 0;
	}

	int getAvgSize()
	{
		return avgsize / count;
	}

	int getMax()
	{
		return max;
	}

	Time getAvgTime()
	{
		return totalQ / count;
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

		std::cout << SimulationExecutive::GetSimulationTime() << ", queue " << _name << ", AddEntity, Entity , queue size, " << _size << std::endl;
		_size++;
		count++;
			if (_size >= max)
			{
				max = _size;
			}
		std::cout << SimulationExecutive::GetSimulationTime() << ", queue " << _name << ", AddEntity, Entity , queue size, " << _size << std::endl;
		((Message*)t)->EnterQ(SimulationExecutive::GetSimulationTime());
	}

	T* GetEntity()
	{
		if (_head == 0) return 0;
		else {
			Node* n = _head;
			T* t = _head->t;
			_head = _head->next;
			//			delete n;

			std::cout << SimulationExecutive::GetSimulationTime() << ", queue " << _name << ", GetEntity, Entity , queue size, " << _size << std::endl;
			_size--;
			avgsize += _size;
			std::cout << SimulationExecutive::GetSimulationTime() << ", queue " << _name << ", GetEntity, Entity , queue size, " << _size << std::endl;
			totalQ += ((Message*)t)->LeaveQ(SimulationExecutive::GetSimulationTime());

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


	Node* _head;
	Node* _tail;
	int _size,max, count, avgsize;
	Time totalQ;
	std::string _name;
};
