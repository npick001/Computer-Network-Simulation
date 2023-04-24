#include "Computer.h"
#include "Network.h"
#include "SimulationExecutive.h"
#include "FIFO.h"
#include <random>// Include the FIFO header

Network* Computer::_computerNetwork = 0;

DistributionValues::DistributionValues()
{
    _min = -1;
    _mode = -1;
    _max = -1;
    _messageGenRate = -1;
    _numEdges = -1;
}

DistributionValues::DistributionValues(double min, double mode, double max, double genRate, int numEdges)
{
    _min = min;
    _mode = mode;
    _max = max;
    _messageGenRate = genRate;
    _numEdges = numEdges;
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

class Computer::SendMessageEA : public EventAction
{
public:
    SendMessageEA(Computer* c, Message* m)
    {
        _c = c;
        _m = m;
    }
    void Execute() {
        _c->SendMessageEM(_m);
    }
private:
    Computer* _c;
    Message* _m;
};

Computer::Computer(Triangular* serviceTimeDist, Exponential* msgGenRateDist, const std::vector<int>& edges, int id)
{
    _serviceTimeDist = serviceTimeDist;
    _msgGenRateDist = msgGenRateDist;
    _edges = edges;
    _id = id;
    _connectedEdges = _edges.size();
    _serviceQueue = new FIFO<Message>("Service Queue"); // Create an instance of the FIFO class
    _busy = false;
    _reserved = false;
    _nextComputer = 0;
    _numGen = 5;
}

void Computer::setStat(StatsHolder* st)
{
    _st = st;
}

Time Computer::getAvgTime()
{
    return _totalService / _numServed;
}

double Computer::getUsage()
{
    return (_totalService / GetSimulationTime())*100;
}

void Computer::SetNetwork(Network* network) {
    _computerNetwork = network;
}

void Computer::Begin() {
    ScheduleEventAt(0.0, new GenerateMessageEA(this));
}

void Computer::Arrive(Message* message)
{
    ScheduleEventIn(0.0, new ArriveEA(this, message));
}

void Computer::GenerateMessageEM()
{
    int finalDestination;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, _computerNetwork->nodes.size() - 1);
    do {
        finalDestination = distrib(gen);
    } while (finalDestination == _id);
    Time t = GetSimulationTime();
    Message* message = new Message(&_computerNetwork->nodes[_id], &_computerNetwork->nodes[finalDestination], t);
    Time genTime = _msgGenRateDist->GetRV();

    // u   se path to determine where it is going.
    ProcessMessage(message);
    std::cout << "Time: " << GetSimulationTime() << "Computer " << _id << ": sending to \tComputer " << message->getDestination()->getId() << "." << std::endl;
    ScheduleEventIn(genTime, new SendMessageEA(this, message));
    // here we would add the different algorithms.

    //std::cout << "Next computer ID: " << path[0] << std::endl;
    //_computerNetwork->nodes[path[0]].Arrive(message);

    // Schedule the routing event

    ScheduleEventIn(genTime, new GenerateMessageEA(this));
};

void Computer::StartServiceEM() {

    _busy = true;
    _reserved = false;

    if (!_serviceQueue->IsEmpty()) {
        Message* message = _serviceQueue->GetEntity();
        std::cout << "Time: " << GetSimulationTime() << "Computer " << _id << "\tStart Service." << std::endl;
        Time serviceTime = _serviceTimeDist->GetRV();
        _totalService += serviceTime;
        int finalDestination = message->getDestination()->getId();
        if (finalDestination == _id) {
            std::cout << "Time: " << GetSimulationTime() << "\tdeleting" << " Message when " << GetSimulationTime() + serviceTime << std::endl;
            _st->addMSG(message);
            message->setEnd(GetSimulationTime());

        }
        else {
            ProcessMessage(message);
            ScheduleEventIn(serviceTime, new SendMessageEA(this, message));


        }
        ScheduleEventIn(serviceTime, new DoneServiceEA(this, _serviceQueue->GetEntity()));



    }
}
void Computer::ArriveEM(Message* message) {
    _numServed++;
    _serviceQueue->AddEntity(message);
    if ((!_busy) && (!_reserved)) {
        _reserved = true;
        ScheduleEventIn(0.0, new StartServiceEA(this));
    }
}
void Computer::DoneServiceEM(Message* message) {

    _busy = false;
    std::cout << "Time: " << GetSimulationTime() << "Computer " << _id << "\tDone Service." << " at " << GetSimulationTime() << std::endl;
    if ((this->GetQueueSize() > 0) && (!_reserved)) {
        ScheduleEventIn(0.0, new StartServiceEA(this));
    }
}

//router
void Computer::ProcessMessage(Message* message) {
    int finalDestination = message->getDestination()->getId();
    std::vector<int> prev;
    if (_computerNetwork->routing_algorithm == RoutingAlgorithm::EQUAL_WEIGHT_DIJKSTRA) {
        prev = _computerNetwork->equal_weight_dijkstra(_id);
    }
    else {
        prev = _computerNetwork->weighted_shortest_path(_id);
    }
    std::vector<int> path = _computerNetwork->getShortestPath(_id, finalDestination, prev);
    // If the path exists, update the message's destination to the next node in the path
    if (path.size() >= 1) {
        int nextDestinationId = path[1];
        _nextComputer = &_computerNetwork->nodes[nextDestinationId];
        // Route the message to the next computer in the network
        std::cout << "Routing message from node " << _id << " to node " << nextDestinationId << std::endl;
    }
    else {
        std::cout << "No path exists between node " << _id << " and node " << finalDestination << std::endl;
    }
}

void Computer::SendMessageEM(Message* message)
{
    std::cout << "Time: " << GetSimulationTime() << "Computer " << _id << " sending to " << message->getDestination()->getId() << std::endl;
    _nextComputer->Arrive(message);
}

int Computer::getId() const {
    return _id;
}

void Computer::SetMyValues(double min, double mode, double max, double genRate, int numEdges)
{
    myValues = DistributionValues(min, mode, max, genRate, numEdges);
}
