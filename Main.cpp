#include "Computer.h"
#include "Distribution.h"
#include "EventSet.h"
#include "Network.h"
#include "SimulationExecutive.h"
#include <vector>
#include <iostream>

using namespace std;


int main() {


    Network network(RoutingAlgorithm::EQUAL_WEIGHT_DIJKSTRA);
    //Network network(RoutingAlgorithm::WEIGHTED_SHORTEST_PATH);
    network.ReadFile("foo.txt");

    // Create a message from node 0 to node 2
    network.CreateMessage(0, 3);


    // Duration of the simulation in seconds


    return 0;
}
