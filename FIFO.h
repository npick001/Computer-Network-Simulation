#pragma once
#include <iostream>
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
		std::cout << GetCurrentSimTime() << ", queue " << _name << ", AddEntity, Entity , queue size, " << _size << std::endl;
		_size++;
		std::cout << GetCurrentSimTime() << ", queue " << _name << ", AddEntity, Entity , queue size, " << _size << std::endl;
	}

	T* GetEntity()
	{
		if (_head == 0) return 0;
		else {
			Node* n = _head;
			T* t = _head->t;
			_head = _head->next;
			//			delete n;
			std::cout << GetCurrentSimTime() << ", queue " << _name << ", GetEntity, Entity , queue size, " << _size << std::endl;
			_size--;
			std::cout << GetCurrentSimTime() << ", queue " << _name << ", GetEntity, Entity , queue size, " << _size << std::endl;
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
	int _size;
	std::string _name;
};
