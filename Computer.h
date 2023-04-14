#pragma once
#include "Distribution.h"
#include "FIFO.h"
#include "Message.h"
#include "SimulationExecutive.h"

class Computer 
{
public:
	Computer();
	int GetQueueSize();
	void ReportStatistics();
private:
	Computer* _connectedEdges;
	FIFO<Message>* _serviceQueue;
	bool _isAvailable;

	class StartServiceEA;
	void StartServiceEM(Message* message);
	class DoneServiceEA;
	void DoneServiceEM(Message* message);
};