#include "Computer.h"
#include "Network.h"
#include "SimulationExecutive.h"
#include "FIFO.h" // Include the FIFO header

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

Computer::Computer(Triangular* serviceTimeDist, Exponential* msgGenRateDist, const std::vector<int>& edges, int id)
{
    _serviceTimeDist = serviceTimeDist;
    _msgGenRateDist = msgGenRateDist;
    _edges = edges;
    _id = id;
    _connectedEdges = _edges.size();
    _serviceQueue = new FIFO<Message>("Service Queue"); // Create an instance of the FIFO class
    _available = true;
}

void Computer::SetNetwork(Network* network) {
    _computerNetwork = network;
}

void Computer::Begin() {
    SimulationExecutive::ScheduleEventIn(0.0, new GenerateMessageEA(this));
}

void Computer::Arrive(Message* message)
{
    SimulationExecutive::ScheduleEventIn(0.0, new ArriveEA(this, message));
}

void Computer::GenerateMessageEM()
{
    // Create a new message
    int finalDestination = rand() % _computerNetwork->GetNetworkSize() - 1;

    while (finalDestination == _id) {
        finalDestination = rand() % _computerNetwork->GetNetworkSize() - 1;
    }

    Message* message = new Message(&_computerNetwork->nodes[_id], &_computerNetwork->nodes[finalDestination], SimulationExecutive::GetSimulationTime());
    std::cout << "Computer " << _id << ": sending to \tComputer " << message->getDestination()->getId() << "." << std::endl;

    // use path to determine where it is going.
    std::vector<int> here = { _id };
    std::vector<int> path = _computerNetwork->getShortestPath(message->getSource()->getId(), message->getDestination()->getId(), here);
    // here we would add the different algorithms.

    std::cout << "Next computer ID: " << path[0] << std::endl;
    _computerNetwork->nodes[path[0]].Arrive(message);

    // Schedule the routing event
    Time genTime = _msgGenRateDist->GetRV();
    SimulationExecutive::ScheduleEventIn(genTime, new GenerateMessageEA(this));
};

void Computer::StartServiceEM() {

    _available = false;
    std::cout << "Computer " << _id << "\tStart Service." << std::endl;
    ProcessMessage();

    Time serviceTime = _serviceTimeDist->GetRV();
    SimulationExecutive::ScheduleEventIn(serviceTime, new DoneServiceEA(this, _serviceQueue->GetEntity()));
}
void Computer::ArriveEM(Message* message) {

    _serviceQueue->AddEntity(message);
    if (_available) {
        SimulationExecutive::ScheduleEventIn(0.0, new StartServiceEA(this));
    }
}
void Computer::DoneServiceEM(Message* message) {

    _available = true;
    std::cout << "Computer " << _id << "\tDone Service." << std::endl;

    if (_serviceQueue->GetSize() > 0) {
        SimulationExecutive::ScheduleEventIn(0.0, new StartServiceEA(this));
    }
}

//router
void Computer::ProcessMessage() {
    if (!_serviceQueue->IsEmpty()) {
        Message* message = _serviceQueue->GetEntity(); // Get the message from the queue
        int finalDestination = message->getDestination()->getId(); // Extract integer ID from Computer object
        if (finalDestination == _id) {
            // The message has arrived at its final destination, handle the arrived message as needed
            // (e.g., log, update statistics, etc.)
            //arrive service action here
            delete message; // Delete the message after processing
        } else {
            // Get the shortest path for routing
            std::vector<int> prev;
            if (_computerNetwork->routing_algorithm == RoutingAlgorithm::EQUAL_WEIGHT_DIJKSTRA) {
                prev = _computerNetwork->equal_weight_dijkstra(_id);
            } else {
                prev = _computerNetwork->weighted_shortest_path(_id);
            }
            std::vector<int> path = _computerNetwork->getShortestPath(_id, finalDestination, prev);
            // If the path exists, update the message's destination to the next node in the path
            if (path.size() >= 1) {
                int nextDestinationId = path[1];
                message->setDestination(&_computerNetwork->nodes[nextDestinationId]);
                // Route the message to the next computer in the network
                std::cout << "Routing message from node " << _id << " to node " << nextDestinationId << std::endl;
            } else {
                std::cout << "No path exists between node " << _id << " and node " << finalDestination << std::endl;
            }
        }
    }
}

int Computer::getId() const {
    return _id;
}

void Computer::SetMyValues(double min, double mode, double max, double genRate, int numEdges)
{
    myValues = DistributionValues(min, mode, max, genRate, numEdges);
}
