#pragma once

#include "Distribution.h"
#include "Message.h"
#include "Network.h"
#include "SimulationExecutive.h"
#include "FIFO.h"
#include <vector>

#define SIM_OUTPUT 0

class Network;
class StatsHolder;

/*
    Holds values related to the triangular and exponential distributions
    for message generation and service times
*/
struct DistributionValues {
    DistributionValues();
    DistributionValues(double min, double mode, double max, double genRate, int numEdges);
    double _min;
    double _mode;
    double _max;
    double _messageGenRate;
    int _numEdges;
};


/*
    Class: Represents a computer node in the network. Handles message generation, 
    arrival, processing, and sending to other connected computers (nodes)
*/
class Computer {
public:

    Computer(Triangular* serviceTimeDist, Exponential* msgGenRateDist, const std::vector<int>& edges, int id);
    /*
        Initializes a computer object with service time distribution,
        message generation rate distribution, edges, and ID
    */

    void Begin();
    /*
        Starts the computer's events and processes
    */

    void Arrive(Message* message);
    /*
        Handles the arrival of a message to the computer
    */

    void SetNetwork(Network* network);
    /*
        Sets the network the computer belongs to
    */

    int GetQueueSize();
    /*
        Returns the size of the computer's queue
    */

    int getId() const;
    /*
        Returns the ID of the computer
    */

    void setStat( StatsHolder* st);
    /*
        Sets the statistics info holder for the computer
    */

    bool operator<(const Computer& c) const { return _id < c._id; }
    /*
        Compares computer IDs for sorting purposes (?)
    */

    Time getAvgTime();
    /*
        Returns the average time spent in the computer's queue
    */

    double getUsage();
    /*
        Returns the usage of the computer as a percentage
    */

    std::vector<int> _edges;
    DistributionValues myValues;
    void SetMyValues(double min, double mode, double max, double genRate, int numEdges);
    /*
        Sets the values of the computer's distribution parameters to be used in print and other places
    */

    FIFO<Message>* _serviceQueue;
        
private:
    class GenerateMessageEA;
    class ArriveEA;
    class StartServiceEA;
    class DoneServiceEA;
    class SendMessageEA;

    // Member variables
    Computer* _nextComputer;
    Triangular* _serviceTimeDist;
    Exponential* _msgGenRateDist;
    int _id;
    int _connectedEdges;
    bool _busy;
    bool _reserved;
    int _numGen;
    static Network* _computerNetwork;
    StatsHolder* _st;
    Time _totalService;
    int _numServed;

    //Methods
    void GenerateMessageEM();
    /*
        Event method for generating messages
    */

    void ArriveEM(Message* message);
    /*
        handling message arrival
    */

    void StartServiceEM();
    /*
        start message service
    */

    void DoneServiceEM(Message* message);
    /*
        completw message service
    */

    void ProcessMessage(Message* message);
    /*
        Determines the next node to route the message to
    */

    void SendMessageEM(Message* message);
    /*
        EM for sending messages to the next node
    */

};