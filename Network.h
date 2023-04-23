#pragma once
#include "Computer.h"
#include <string>
#include <vector>
#include <istream>

enum class RoutingAlgorithm {
    EQUAL_WEIGHT_DIJKSTRA,
    WEIGHTED_SHORTEST_PATH
};

class Network {
public:
    Network(RoutingAlgorithm algorithm) : routing_algorithm(algorithm) {} // Initialize routing_algorithm in the constructor
    void ReadFile(std::string filename);
    void setRoutingAlgorithm(RoutingAlgorithm algorithm) { routing_algorithm = algorithm; } // Add the setter method
    RoutingAlgorithm routing_algorithm;
    int GetEdgeWeight(Computer* computer);
    void addNode(const Computer& node);
    void parseGraphFromFile(const std::string& filename);
    std::vector<int>equal_weight_dijkstra(int source);
    std::vector<int>getShortestPath(int source, int destination, const std::vector<int>& prev);
    //void routeMessage(Message* message);
    std::vector<int>weighted_shortest_path(int source);
    void CreateMessage(int sourceNodeIndex, int destinationNodeIndex);

    std::vector<Computer> nodes;
private:
    static Computer* _computerNetwork;
    bool is_valid_node_index(int index, int num_nodes);
    int read_label(std::istream& in);
    void read_edges(std::istream& in, int num_edges, std::vector<int>& edges, int num_nodes, int current_node);
    void read_triangular(std::istream& in, double& min, double& mode, double& max);
    void read_exponential(std::istream& in, double& rate);
    void print_graph(const Network& _computerNetwork);
    void print_shortest_path_distances(const std::vector<int>& dist);
};
