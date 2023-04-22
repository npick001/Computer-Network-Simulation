#pragma once
#include "Distribution.h"
#include "FIFO.h"
#include "SimulationExecutive.h"

class Message; // Forward declaration

class Computer
{
public:
    Triangular serviceTimeDist;
    Exponential msgGenRateDist;
    std::vector<int> edges;

    Computer(Triangular& serviceTimeDist, Exponential& msgGenRateDist, const std::vector<int>& edges, int id);
    int GetQueueSize();
    void ReportStatistics();
    int find_next_node(const std::vector<int>& dist, const std::vector<Computer>& nodes);
    double GetExpectedCost();
    int getId() const { return _id; }

private:
    Computer* _connectedEdges;
    int _id;
    FIFO<Message>* _serviceQueue;
    bool _available;
    Distribution* _genRate;
    class GenerateMessageEA;
    void GenerateMessageEM();
    class ArriveEA;
    void ArriveEM(Message* message);
    class StartServiceEA;
    void StartServiceEM();
    class DoneServiceEA;
    void DoneServiceEM(Message* message);
};
