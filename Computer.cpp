#include "Computer.h"

Computer::Computer()
{
}

int Computer::GetQueueSize()
{
	return 0;
}

void Computer::ReportStatistics()
{
}

class Computer::StartServiceEA : public EventAction
{
public:
	StartServiceEA(Computer* c, Message* m) {
		_c = c;
		_m = m;
	}

	void Execute() {
		_c->StartServiceEM(_m);
	}
private:
	Computer* _c;
	Message* _m;
};
void Computer::StartServiceEM(Message* message) {

}
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
void Computer::DoneServiceEM(Message* message) {

}