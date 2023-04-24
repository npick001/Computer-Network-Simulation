#include "Message.h"
#include "Computer.h"
int Message::nextID = 0;
Message::Message(Computer* source, Computer* destination, Time creationTime)
{
	_source = source;
	_destination = destination;
	_start = creationTime;
	_QueueT = 0;
	_timesStopped = 0;
    ID = nextID++;
}

bool Message::operator<(const Message& m) const
{
    return ID < m.ID;
}

Message::~Message()
{
}

Computer* Message::getSource() const
{
    return _source;
}

Computer* Message::getDestination() const
{
    return _destination;
}

void Message::setDestination(Computer* computer) {
    _destination = computer;
}

void Message::EnterQ(Time Eq)
{
    _enterQ = Eq;
    _timesStopped++;
}

Time Message::LeaveQ(Time Lq)
{
    _exitQ = Lq;
    _QueueT += (_exitQ - _enterQ);

    return(_exitQ - _enterQ);
}

void Message::ReachEnd()
{
    _end = SimulationExecutive::GetSimulationTime();
    this->ComputeStats();
}

void Message::ComputeStats()
{
    commsTime = _end - _start;
    avgWait = _QueueT / _timesStopped;
}