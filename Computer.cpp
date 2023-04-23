#include "Computer.h"

Computer::Computer(Triangular& serviceTimeDist, Exponential& msgGenRateDist, const std::vector<int>& edges, int id)
    : serviceTimeDist(serviceTimeDist), msgGenRateDist(msgGenRateDist), edges(edges), _id(id)
{
    _connectedEdges = 0;
    _serviceQueue = new FIFO<Message>("Service Queue");
    _available = true;
    _genRate = &msgGenRateDist;
}

void Computer::SetNetwork(Network* network) {
    _computerNetwork = network;
}

int Computer::GetQueueSize() {
    return _serviceQueue->GetSize();
}

void Computer::ReportStatistics()
{
}

class Computer::GenerateMessageEA : public EventAction
{
public:
	GenerateMessageEA(Computer* c) {
		_c = c;
	}

	void Execute() {
		_c->GenerateMessageEM();
	}
private:
	Computer* _c;
};

class Computer::ArriveEA : public EventAction
{
public:
	ArriveEA(Computer* c, Message* m) {
		_c = c;
		_m = m;
	}

	void Execute() {
		_c->ArriveEM(_m);
	}
private:
	Computer* _c;
	Message* _m;
};

class Computer::StartServiceEA : public EventAction
{
public:
	StartServiceEA(Computer* c) {
		_c = c;
	}

	void Execute() {
		_c->StartServiceEM();
	}
private:
	Computer* _c;
	
};

class Computer::DoneServiceEA : public EventAction
{
public:
	DoneServiceEA(Computer* c, Message* m) {
		_c = c;
		_m = m;
	}

	void Execute() {
		_c->DoneServiceEM(_m);
	}
private:
	Computer* _c;
	Message* _m;
};

void Computer::StartServiceEM() {

	_available = false;
	SimulationExecutive::ScheduleEventIn(_genRate->GetRV(), new DoneServiceEA(this, _serviceQueue->GetEntity()));
}

void Computer::DoneServiceEM(Message* message) {

	_available = true;

	if (_serviceQueue->GetSize() > 0) {
		SimulationExecutive::ScheduleEventIn(0.0, new StartServiceEA(this));
	}
}

void Computer::ArriveEM(Message* message) {

	_serviceQueue->AddEntity(message);
	if (_available) {
		SimulationExecutive::ScheduleEventIn(0.0, new StartServiceEA(this));
	}
}

void Computer::GenerateMessageEM()
{
	Time genTime = _genRate->GetRV();

	// send to right place

	SimulationExecutive::ScheduleEventIn(genTime, new GenerateMessageEA(this));
};

int Computer::getId() const {
    return _id;
}
