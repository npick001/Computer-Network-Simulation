#include "Computer.h"
#include "Distribution.h"
#include "EventSet.h"
#include "Network.h"
#include "SimulationExecutive.h"

using namespace std;

void main() {
	StatsHolder* sh = new StatsHolder;

	Time endTime = 1000;
	InitializeSimulation();


	//Network network(RoutingAlgorithm::EQUAL_WEIGHT_DIJKSTRA);
	Network network(RoutingAlgorithm::WEIGHTED_SHORTEST_PATH);
	network.SetStats(sh);
	network.ReadFile("foo.txt");

	cout << endl << "Simulation Starting..." << endl << endl;

	RunSimulation(endTime);

	network.addNodestoStat();
	sh->ReportStats();
}