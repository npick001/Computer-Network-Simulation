#pragma once
#include "Computer.h"
#include "Stats.h"
#include <string>
#include <vector>
#include <istream>
class Computer;
class Message;
class StatsHolder;


/*
    Specifies the possible routing algorithms to be used in the network
*/
enum class RoutingAlgorithm {
    EQUAL_WEIGHT_DIJKSTRA,
    WEIGHTED_SHORTEST_PATH
};


class Network {
public:
    Network(RoutingAlgorithm algorithm) : routing_algorithm(algorithm) {}
    /*
        Initializes a new Network object with the specified routing algorithm
    */

    std::vector<Computer> nodes;
     /*
        Stores the computers (nodes) present in the network
    */


    void ReadFile(std::string filename);
     /*
        Reads the network graph from the file and call parser
    */


    void setRoutingAlgorithm(RoutingAlgorithm algorithm) { routing_algorithm = algorithm; }
     /*
        Sets the routing algorithm to be used by the network
    */


    RoutingAlgorithm routing_algorithm;
    /*
        Represents the routing algorithm used in the network
    */


    int GetEdgeWeight(Computer* computer);
     /*
        Calculates and returns the edge weight for the specified computer
    */


    void addNode(Computer node);
    /*
        Adds a computer node to the network's nodes vector
    */

    void parseGraphFromFile(const std::string& filename);
    /*
        Parses the network graph from a file with the specified filename
    */

    std::vector<int>equal_weight_dijkstra(int source);
     /*
        returns the shortest paths from a source node to all other nodes. Used in getShortestPath
    */

    std::vector<int>getShortestPath(int source, int destination, const std::vector<int>& prev);
     /*
        Computes the shortest path between a source and destination node using the path information in the prev vector. Does
        the actual pathfinding
    */


    std::vector<int>weighted_shortest_path(int source);
    /*
        returns the weighted shortest path algorithm for finding the shortest paths from a source node. Used in getShortestPath
    */

    int GetNetworkSize();
     /*
        Returns the total number of nodes (computers) in the network
    */

    void SetStats(StatsHolder* st);
    void addNodestoStat();
    /*
        Adds computer nodes to the StatsHolder object
    */


private:

    StatsHolder* _st;
    bool is_valid_node_index(int index, int num_nodes);
     /*
        Determines if the given index is a valid node index within the network
    */


    int read_label(std::istream& in);
     /*
        Helper function/input validation that reads a node label from the input stream and returns the node ID
    */


    void read_edges(std::istream& in, int num_edges, std::vector<int>& edges, int num_nodes, int current_node);
    /*
        Helper function/input validation that reads the edge information from the input stream and populates the edges vector
    */


    void read_triangular(std::istream& in, double& min, double& mode, double& max);
     /*
        Helper function/input validation that reads the parameters of an triangular distribution from the input stream
    */


    void read_exponential(std::istream& in, double& rate);
     /*
        Helper function/input validation that reads the parameters of an exponential distribution from the input stream
    */


    void print_graph(const Network& _computerNetwork);
    void print_shortest_path_distances(const std::vector<int>& dist);

};

