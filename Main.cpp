#include "Computer.h"
#include "Distribution.h"
#include "EventSet.h"
#include "Network.h"
#include "SimulationExecutive.h"

using namespace std;

void main() {
	SimulationExecutive::InitializeSimulation();

	Network network(RoutingAlgorithm::EQUAL_WEIGHT_DIJKSTRA);
	network.ReadFile("foo.txt");
	//myNetwork.equal_weight_dijkstra(0);

	SimulationExecutive::RunSimulation();
}