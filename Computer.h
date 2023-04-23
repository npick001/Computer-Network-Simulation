#pragma once

#include "FIFO.h"
#include <vector>
#include "Distribution.h"
#include "Message.h"
#include "Network.h"
#include "SimulationExecutive.h"

class Message;
class Network;

class Computer {
public:
    Computer(Triangular& serviceTimeDist, Exponential& msgGenRateDist, const std::vector<int>& edges, int id);
    void SetNetwork(Network* _network);
    void AddMessageToSource(Message* message);
    int GetQueueSize();
    void ReportStatistics();
    std::vector<int> edges;
    int getId() const;

private:
    // EventAction subclasses
    class GenerateMessageEA;
    class ArriveEA;
    class StartServiceEA;
    class DoneServiceEA;

    // Event methods
    void GenerateMessageEM();
    void ArriveEM(Message* message);
    void StartServiceEM();
    void DoneServiceEM(Message* message);

    // Member variables
    Triangular& serviceTimeDist;
    Exponential& msgGenRateDist;
    int _id;
    int _connectedEdges;
    FIFO<Message>* _serviceQueue;
    bool _available;
    Distribution* _genRate;
    Network* _computerNetwork;
};
