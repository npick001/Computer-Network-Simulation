#ifndef COMPUTER_H
#define COMPUTER_H

#include "Distribution.h"
#include "Message.h"
#include "Network.h"
#include "SimulationExecutive.h"
#include "FIFO.h"
#include <vector>

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
    // Event methods
    void GenerateMessageEM();
    void ArriveEM(Message* message);
    void ProcessMessage(); // Add the ProcessMessage method declaration
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

#endif // COMPUTER_H
