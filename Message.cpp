#include "Message.h"

Message::Message()
{
	_sc = *(new StatContainer);
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
	_sc.LeaveQ(Lq);
}
