#include "Computer.h"
#include "Distribution.h"
#include "EventSet.h"
#include "Network.h"
#include "SimulationExecutive.h"

using namespace std;

void main() {
	StatsHolder* SH = new StatsHolder;
	Time endTime = 1000;
	SimulationExecutive::InitializeSimulation();
	Network network(RoutingAlgorithm::EQUAL_WEIGHT_DIJKSTRA);
	network.setStats(SH);
	network.ReadFile("foo.txt");

	cout << endl << "Simulation Starting..." << endl << endl;


	SimulationExecutive::RunSimulation(endTime);
}