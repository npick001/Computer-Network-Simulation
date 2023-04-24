#pragma once

#include "Distribution.h"
#include "Message.h"
#include "Network.h"
#include "SimulationExecutive.h"
#include "FIFO.h"
#include <vector>

class Network;

struct DistributionValues {
    DistributionValues();
    DistributionValues(double min, double mode, double max, double genRate, int numEdges);

    double _min;
    double _mode;
    double _max;
    double _messageGenRate;
    int _numEdges;
};

class Computer {
public:
    Computer();
    Computer(Triangular* serviceTimeDist, Exponential* msgGenRateDist, const std::vector<int>& edges, int id);
    void Begin();
    void Arrive(Message* message);
    void SetNetwork(Network* network);
    int GetQueueSize();
    bool operator<(const Computer& c) const;
    void ReportStatistics();
    void SetStat(StatsHolder* st) { _st = st; }
    FIFO<Message>* GetFIFO() { return _serviceQueue; }
    int getId() const;
    std::vector<int> _edges;
    void SetMyValues(double min, double mode, double max, double genRate, int numEdges);
    DistributionValues myValues;
    Time getAvgTime() { return totalService / numServed; }
    double getUsage() { return (totalService / SimulationExecutive::GetSimulationTime())*100; }
private:
    // Event methods
    class GenerateMessageEA;
    class ArriveEA;
    class StartServiceEA;
    class DoneServiceEA;
    void GenerateMessageEM();
    void ArriveEM(Message* message);
    void StartServiceEM();
    void DoneServiceEM(Message* message);
    void ProcessMessage(); // Add the ProcessMessage method declaration

    // Member variables
    Time totalService;
    StatsHolder* _st;
    int numServed;
    Triangular* _serviceTimeDist;
    Exponential* _msgGenRateDist;
    int _id;
    int _connectedEdges;
    FIFO<Message>* _serviceQueue;
    bool _available;
    Network* _computerNetwork;
};