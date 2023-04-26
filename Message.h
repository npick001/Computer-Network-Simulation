#pragma once
#include "Stats.h"
#include "Computer.h"
#include "SimulationExecutive.h"
#include <iostream>

class Computer;
class Message
{
public:
    Message(Computer* source, Computer* destination, Time creationTime);
    ~Message();

    void EnterQ(Time);
    /*
        Records the time when the message enters the queue
    */

    Time LeaveQ(Time);
    /*
        Records the time when the message leaves the queue
    */

    int getID() { return _id; }
    /*
        Returns the ID of the message
    */

    bool operator<(const Message& m) const { return _id > m._id; }

    void setDestination(Computer* computer);
    /*
        Sets the destination computer for the message
    */
    
    Computer* getSource() const;
    /*
        Returns the source computer of the message
    */

    Computer* getDestination() const;
    /*
        Returns the destination computer of the message
    */

    void setEnd(Time end) { _destinationTime = end; }
    /*
        Sets the time when the message reaches its destination
    */

    Time getCommTime() { return _destinationTime - _creationTime; }
    /*
        Returns the communication time of the message
    */

    Time getWaitTime() { return _waitTime; }
    /*
        Returns the wait time of the message
    */
private:
    Computer* _source;
    Computer* _destination;
    int _id;
    Time _creationTime;
    Time _destinationTime;
    Time _waitTime,_enterQ,_exitQ,_totalTime;
	int _timesStopped; // number of wait times
};
