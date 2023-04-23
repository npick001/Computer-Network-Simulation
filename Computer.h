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

private:
    // EventAction subclasses
    class GenerateMessageEA : public EventAction {
    public:
        GenerateMessageEA(Computer* c);
        void Execute();
    private:
        Computer* _c;
    };

    class ArriveEA : public EventAction {
    public:
        ArriveEA(Computer* c, Message* m);
        void Execute();
    private:
        Computer* _c;
        Message* _m;
    };

    // Event methods
    void GenerateMessageEM();
    void ArriveEM(Message* message);

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
