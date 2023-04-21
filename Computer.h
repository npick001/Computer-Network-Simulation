#pragma once
#include "Distribution.h"
#include "FIFO.h"
#include "Message.h"
#include "SimulationExecutive.h"

class Computer 
{
public:
	Computer(Distribution* generationRate);
	int GetQueueSize();
	void ReportStatistics();
private:
	Computer* _connectedEdges;
	FIFO<Message>* _serviceQueue;
	bool _available;

	Distribution* _genRate;

	class GenerateMessageEA;
	void GenerateMessageEM();
	class ArriveEA;
	void ArriveEM(Message* message);
	class StartServiceEA;
	void StartServiceEM();
	class DoneServiceEA;
	void DoneServiceEM(Message* message);

};