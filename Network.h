#pragma once
#include "Computer.h"
#include <string>
#include <vector>
#include <istream>

class Network {
public:
    Network() {}

    std::vector<Computer> nodes;

	int GetEdgeWeight(Computer* computer);
    void ReadFile(std::string filename);
    void addNode(const Computer& node);
    void parseGraphFromFile(const std::string& filename);
	void equal_weight_dijkstra(int source);

private:
	std::string read_label(std::istream& in);
	static Computer* _computerNetwork;
    bool is_valid_node_index(int index, int num_nodes);
    void read_edges(std::istream& in, int num_edges, std::vector<int>& edges, int num_nodes, int current_node);
    void read_triangular(std::istream& in, double& min, double& mode, double& max);
    void read_exponential(std::istream& in, double& rate);
	void print_graph(const Network& _computerNetwork);
	void print_shortest_path_distances(const std::vector<int>& dist);
};
