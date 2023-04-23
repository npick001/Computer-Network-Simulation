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

void Computer::GenerateMessageEM()
{
    Time genTime = _genRate->GetRV();

    // send to right place

//    SimulationExecutive::ScheduleEventIn(genTime, new GenerateMessageEA(this));
};



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


