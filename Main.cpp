#include "Computer.h"
#include "Distribution.h"
#include "EventSet.h"
#include "Network.h"
#include "SimulationExecutive.h"

using namespace std;

int main() {

	Network myNetwork;
	myNetwork.ReadFile("foo.txt");
	//myNetwork.equal_weight_dijkstra(0);
    return 0;
	// Find the shortest path based on the expected cost at each node
	//myNetwork.dijkstra(0, true);

}
