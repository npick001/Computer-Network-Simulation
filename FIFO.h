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
		_total = 0;
		_max = 0;
		_cdfWaits = 0;
	}

	double getAvgTime()
	{
		return _cdfWaits / _total;
	}

	double getAvgSize()
	{
		double temp = (_sumSizes / _total);
		return temp;
	}

	double getMax()
	{
		return _max;
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

		//std::cout << GetSimulationTime() << ", queue, " << _name << ", AddEntity, Entity , queue size, " << _size << std::endl;
		_size++;
		if (_size > _max)
		{
			_max = _size;
		}
		_total++;
		//std::cout << GetSimulationTime() << ", queue, " << _name << ", AddEntity, Entity , queue size, " << _size << std::endl;
		((Message*)t)->EnterQ(GetSimulationTime());
	}

	T* GetEntity()
	{
		if (_head == 0) return 0;
		else {
			Node* n = _head;
			T* t = _head->t;
			_head = _head->next;
			//			delete n;

			//std::cout << GetSimulationTime() << ", queue, " << _name << ", GetEntity, Entity , queue size, " << _size << std::endl;
			_size--;
		//	std::cout << GetSimulationTime() << ", queue, " << _name << ", GetEntity, Entity , queue size, " << _size << std::endl;
			_cdfWaits += ((Message*)t)->LeaveQ(GetSimulationTime());
			_sumSizes += _size;
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
	int _size, _max, _count, _sumSizes;
	double  _total;
	Time total, _cdfWaits;
	std::string _name;
};
