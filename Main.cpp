#include "Computer.h"
#include "Distribution.h"
#include "EventSet.h"
#include "Network.h"
#include "SimulationExecutive.h"


int main() {
	return 0;

	Network myNetwork;
	myNetwork.ReadFile("foo.txt");

	// Find the shortest path minimizing the number of edges traversed
	myNetwork.equal_weight_dijkstra(0);

	// Find the shortest path based on the expected cost at each node
	//myNetwork.dijkstra(0, true);

}
