#ifndef NETWORK_H
#define NETWORK_H

#include "Computer.h"
#include <vector>
#include <string>

#ifdef _WIN32
#define NETWORK_API __declspec(dllexport)
#else
#define NETWORK_API
#endif

class Network {
public:
    static Computer* _computerNetwork;
    std::vector<Computer> nodes;

    NETWORK_API void ReadFile(std::string filename);
    NETWORK_API int GetEdgeWeight(Computer* computer);
    NETWORK_API void equal_weight_dijkstra(int source);

private:
    void addNode(const Computer& node);
    bool is_valid_node_index(int index, int num_nodes);
    std::string read_label(std::istream& in);
    void read_edges(std::istream& in, int num_edges, std::vector<int>& edges, int num_nodes, int current_node);
    void read_triangular(std::istream& in, double& min, double& mode, double& max);
    void read_exponential(std::istream& in, double& rate);
    void parseGraphFromFile(const std::string& filename);
    void print_shortest_path_distances(const std::vector<int>& dist);
    void print_graph(const Network& _computerNetwork);
};

#endif
