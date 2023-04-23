#include "Message.h"

int Message::nextID = 0;

Message::Message()
{
	_sc = *(new StatContainer);
	_id = nextID++;
}

Message::~Message()
{
	delete &_sc;
}

void Message::ReportStatistics()
{
}

void Message::EnterQ(Time Eq)
{
	_sc.EnterQ(Eq);
}

Time Message::LeaveQ(Time Lq)
{
	return _sc.LeaveQ(Lq);
}
