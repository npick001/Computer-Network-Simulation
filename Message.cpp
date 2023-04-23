#include "Message.h"

Message::Message()
{
	_timesStopped = 0;
	_waitTime = 0;
}

Message::~Message()
{
}

void Message::ReportStatistics()
{
}

void Message::EnterQ(Time Eq)
{
	_enterQ = Eq;
}

Time Message::LeaveQ(Time Lq)
{
	_exitQ = Lq;
	_waitTime += (_exitQ - _enterQ);
	_timesStopped++;
}
