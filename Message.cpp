#include "Message.h"

Message::Message(Computer* source, Computer* destination)
{
	_source = source;
	_destination = destination;

	_creationTime = SimulationExecutive::GetSimulationTime();
	_destinationTime = -1;
	_waitTime = 0;

	_timesStopped = 0;
}

Message::~Message()
{
}

void Message::ReportStatistics()
{
}
