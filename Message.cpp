#include "Message.h"
#include "Computer.h"
int NextID = 0;

Message::Message(Computer* source, Computer* destination, Time creationTime)
{
	_id = NextID++;
	_source = source;
	_destination = destination;
	_creationTime = creationTime;
	_destinationTime = -1;
	_waitTime = 0;
	_timesStopped = 0;
	_enterQ = 0;
	_exitQ = 0;
}

Message::~Message()
{
}

void Message::EnterQ(Time eq)
{
	_enterQ = eq;
}

Time Message::LeaveQ(Time lq)
{
	_exitQ = lq;
	_waitTime += (_exitQ - _enterQ);
	return (_exitQ - _enterQ);
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
