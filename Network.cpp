#include "Network.h"
#include "Distribution.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <queue>
#ifdef _WIN32
#define NETWORK_API __declspec(dllexport)
#else
#define NETWORK_API
#endif


Computer* Network::_computerNetwork = 0;


NETWORK_API void Network::ReadFile(std::string filename) {
    try {
        parseGraphFromFile(filename);
        print_graph(*this);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

NETWORK_API int Network::GetEdgeWeight(Computer* computer) {
    return computer->GetQueueSize();
}

void Network::addNode(const Computer& node) {
    nodes.push_back(node);
}

bool Network::is_valid_node_index(int index, int num_nodes) {
    return index >= 0 && index < num_nodes;
}

std::string Network::read_label(std::istream& in) {
    std::string label;
    std::getline(in, label, ':');
    return label;
}

void Network::read_edges(std::istream& in, int num_edges, std::vector<int>& edges, int num_nodes, int current_node) {
    std::string line;
    std::getline(in, line);
    std::istringstream iss(line);
    std::string label;

    for (int j = 0; j < num_edges; ++j) {
        if (j < num_edges - 1) {
            std::getline(iss, label, ',');
        } else {
            std::getline(iss, label);
        }
        std::istringstream edge_iss(label);

        if (!(edge_iss >> edges[j]) || !is_valid_node_index(edges[j], num_nodes) || edges[j] == current_node) {
            throw std::runtime_error("Invalid edge data");
        }
    }
}


void Network::read_triangular(std::istream& in, double& min, double& mode, double& max) {
    char ch;
    in >> min >> ch >> mode >> ch >> max;

    if (ch != ',') {
        throw std::runtime_error("Invalid triangular distribution format");
    }
}

void Network::read_exponential(std::istream& in, double& rate) {
    if (!(in >> rate) || rate <= 0) {
        throw std::runtime_error("Invalid exponential distribution format");
    }
}


void Network::parseGraphFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    int num_nodes;

    if (!(file >> num_nodes) || num_nodes <= 0) {
        throw std::runtime_error("Invalid number of nodes");
    }

    file.ignore(); // Ignore the newline character

    for (int i = 0; i < num_nodes; ++i) {
        read_label(file); // Read and ignore the "Node X:" label

        double min, mode, max;
        read_triangular(file, min, mode, max); // Read triangular distribution values for service time

        double msg_gen_rate;
        read_exponential(file, msg_gen_rate); // Read exponential distribution value for message generation rate

        int num_edges;
        if (!(file >> num_edges) || num_edges < 0) {
            throw std::runtime_error("Invalid number of edges");
        }

        file.ignore(); // Ignore the newline character

        std::vector<int> edges(num_edges);
        read_edges(file, num_edges, edges, num_nodes, i);

        Triangular serviceTimeDist(min, mode, max);
        Exponential msgGenRateDist(msg_gen_rate);
        Computer computer(serviceTimeDist, msgGenRateDist, edges);
        addNode(computer);
    }

    file >> std::ws; // Ignore any trailing whitespace
    if (!file.eof()) {
        throw std::runtime_error("Extra data found in the file");
    }

    file.close();
}





// int Computer::find_next_node(const std::vector<int>& dist, const std::vector<Computer>& nodes) {
//     int next_node = -1;
//     int min_cost = std::numeric_limits<int>::max();

//     for (int v : edges) {
//         int cost = dist[v] + nodes[v].GetExpectedCost();

//         if (cost < min_cost) {
//             min_cost = cost;
//             next_node = v;
//         }
//     }

//     return next_node;
// }


void Network::print_shortest_path_distances(const std::vector<int>& dist) {
    std::cout << "Shortest path distances from the source node:\n";

    for (size_t i = 0; i < dist.size(); ++i) {
        if (dist[i] == std::numeric_limits<int>::max()) {
            std::cout << "Node " << i << ": INFINITY\n";
        } else {
            std::cout << "Node " << i << ": " << dist[i] << "\n";
        }
    }
}

NETWORK_API void Network::equal_weight_dijkstra(int source) {
    const int num_nodes = nodes.size();
    std::vector<int> dist(num_nodes, std::numeric_limits<int>::max());
    std::vector<bool> visited(num_nodes, false);

    dist[source] = 0;
    std::queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (visited[u]) continue;
        visited[u] = true;

        const Computer& curr_computer = nodes[u];

        for (int v : curr_computer.edges) {
            int alt = dist[u] + 1;

            if (alt < dist[v]) {
                dist[v] = alt;
                q.push(v);
            }
        }
    }

    print_shortest_path_distances(dist);
}


void Network::print_graph(const Network& _computerNetwork) {
    for (size_t i = 0; i < _computerNetwork.nodes.size(); ++i) {
        const auto& computer = _computerNetwork.nodes[i];
        std::cout << "Node " << i << ":\n";

        std::cout << "  Service time (triangular): " << ", "
                   << ", " << "\n";
        std::cout << "  Message generation rate (exponential): " << "\n";

        std::cout << "  Edges: ";
        for (size_t j = 0; j < computer.edges.size(); ++j) {
            std::cout << computer.edges[j];
            if (j < computer.edges.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}


