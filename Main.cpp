#include "Computer.h"
#include "Distribution.h"
#include "EventSet.h"
#include "Network.h"
#include "SimulationExecutive.h"

using namespace std;

void main() {

	Network network(RoutingAlgorithm::EQUAL_WEIGHT_DIJKSTRA);
	network.ReadFile("foo.txt");

	cout << endl << "Simulation Starting..." << endl << endl;
	Time endTime = 1000;
	SimulationExecutive::InitializeSimulation();

	SimulationExecutive::RunSimulation(endTime);
}