#include "Computer.h"
#include "Network.h"
#include "SimulationExecutive.h"
#include "FIFO.h" // Include the FIFO header

Computer::Computer(Triangular& serviceTimeDist, Exponential& msgGenRateDist, const std::vector<int>& edges, int id)
    : serviceTimeDist(serviceTimeDist), msgGenRateDist(msgGenRateDist), edges(edges), _id(id)
{
    _connectedEdges = 0;
    _serviceQueue = new FIFO<Message>("Service Queue"); // Create an instance of the FIFO class
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
void Computer::GenerateMessageEM()
{
    Time genTime = _genRate->GetRV();

    // Create a new message
    int finalDestination = rand() % _computerNetwork->nodes.size();
    Message* message = new Message(&_computerNetwork->nodes[_id], &_computerNetwork->nodes[finalDestination], genTime);

    // Add the new message to the queue
    _serviceQueue.AddEntity(&message);

    // Schedule the routing event
    SimulationExecutive::ScheduleEventIn(genTime, new GenerateMessageEA(this));
};
void Computer::StartServiceEM() {

    _available = false;
    SimulationExecutive::ScheduleEventIn(_genRate->GetRV(), new DoneServiceEA(this, _serviceQueue.GetEntity()));
}
void Computer::ArriveEM(Message* message) {

    _serviceQueue.AddEntity(&message);
    if (_available) {
        SimulationExecutive::ScheduleEventIn(0.0, new StartServiceEA(this));
    }
}
void Computer::DoneServiceEM(Message* message) {

    _available = true;

    if (_serviceQueue->GetSize() > 0) {
        SimulationExecutive::ScheduleEventIn(0.0, new StartServiceEA(this));
    }
}

//router
void Computer::ProcessMessage() {
    if (!_serviceQueue.IsEmpty()) {
        Message* message = _serviceQueue.GetEntity(); // Get the message from the queue
        int finalDestination = message->getDestination()->getId(); // Extract integer ID from Computer object
        if (finalDestination == _id) {
            // The message has arrived at its final destination, handle the arrived message as needed
            // (e.g., log, update statistics, etc.)
            //arrive service action here
            delete message; // Delete the message after processing
        } else {
            // Get the shortest path for routing
            std::vector<int> prev;
            if (_computerNetwork->routing_algorithm == Network::RoutingAlgorithm::EQUAL_WEIGHT_DIJKSTRA) {
                prev = _computerNetwork->equal_weight_dijkstra(_id);
            } else {
                prev = _computerNetwork->weighted_shortest_path(_id);
            }
            std::vector<int> path = _computerNetwork->getShortestPath(_id, finalDestination, prev);
            // If the path exists, update the message's destination to the next node in the path
            if (path.size() > 1) {
                int nextDestinationId = path[1];
                message->setDestination(&_computerNetwork->nodes[nextDestinationId]);
                // Route the message to the next computer in the network
                std::cout << "Routing message from node " << _id << " to node " << nextDestinationId << std::endl;
            } else {
                std::cout << "No path exists between node " << _id << " and node " << finalDestination << std::endl;
            }
        }
        // Remove the message from the queue after processing
        _serviceQueue.RemoveEntity();
        //done service action
        // Schedule the next message processing
        if (!_serviceQueue.IsEmpty()) {
            Time processingTime = serviceTimeDist;
            SimulationExecutive::ScheduleEventIn(processingTime, new ArriveEA(this, _serviceQueue.ViewEntity()));
        }
    }
}




//void Computer::ArriveEM(Message* message) {
//    _serviceQueue->AddEntity(message); // Add the incoming message to the FIFO queue
 //   if (_available) {
 //       SimulationExecutive::ScheduleEventIn(0.0, new StartServiceEA(this));
 //   }
//}

int Computer::getId() const {
    return _id;
}


