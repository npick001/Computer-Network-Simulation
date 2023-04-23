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
    void ReportStatistics();
    int getId() const;

    std::vector<int> _edges;
    void SetMyValues(double min, double mode, double max, double genRate, int numEdges);
    DistributionValues myValues;
private:
    // Event methods
    class GenerateMessageEA;
    class ArriveEA;
    class StartServiceEA;
    class DoneServiceEA;
    class SendMessageEA;
    void GenerateMessageEM();
    void ArriveEM(Message* message);
    void StartServiceEM();
    void DoneServiceEM(Message* message);
    void ProcessMessage(Message* message);
    void SendMessageEM(Message* message);

    // Member variables
    Computer* _nextComputer;
    Triangular* _serviceTimeDist;
    Exponential* _msgGenRateDist;
    int _id;
    int _connectedEdges;
    FIFO<Message>* _serviceQueue;
    bool _available;
    static Network* _computerNetwork;
};
