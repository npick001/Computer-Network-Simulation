#include "Computer.h"

Computer::Computer(Triangular& serviceTimeDist, Exponential& msgGenRateDist, const std::vector<int>& edges, int id)
    : serviceTimeDist(serviceTimeDist), msgGenRateDist(msgGenRateDist), edges(edges), _id(id)
{
<<<<<<< HEAD
	_connectedEdges = 0;
	_serviceQueue = new FIFO<Message>("Service Queue");
	_available = true;
	_genRate = generationRate;
=======
    _connectedEdges = 0;
    _serviceQueue = new FIFO<Message>("Service Queue");
    _available = true;
    _genRate = &msgGenRateDist;
>>>>>>> pepper2.0
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

void Computer::GenerateMessageEM()
{
    Time genTime = _genRate->GetRV();

    // send to right place

//    SimulationExecutive::ScheduleEventIn(genTime, new GenerateMessageEA(this));
};

<<<<<<< HEAD
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

class Computer::ArriveEA : public EventAction
{
public:
	ArriveEA(Computer* c, Message* m) {
		_c = c;
		_m = m;
	}
=======
>>>>>>> pepper2.0


<<<<<<< HEAD
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
=======
void Computer::ArriveEM(Message* message) {

    _serviceQueue->AddEntity(message);
    if (_available) {
//        SimulationExecutive::ScheduleEventIn(0.0, new StartServiceEA(this));
    std::cout <<"stuff";
    }
}

int Computer::getId() const {
    return _id;
}


>>>>>>> pepper2.0
