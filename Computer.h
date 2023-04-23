#pragma once
#include "Distribution.h"
#include "FIFO.h"
#include "Message.h"
#include "SimulationExecutive.h"

class Computer
{
public:
    Triangular serviceTimeDist;
    Exponential msgGenRateDist;
    std::vector<int> edges;

    Computer(Triangular& serviceTimeDist, Exponential& msgGenRateDist, const std::vector<int>& edges);
    int GetQueueSize();
    void ReportStatistics();
    int find_next_node(const std::vector<int>& dist, const std::vector<Computer>& nodes);
    double GetExpectedCost();

private:
    Computer* _connectedEdges;
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
    double cdfService;
    double numServed;
};
