#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "ACOGraph.h"
#include "ACO.h"

class Ant {
private:
    ACO* colony;
    ACOGraph* graph;
    double solution_cost;
    std::vector<int> solution;
    std::vector<std::vector<double>> pheromone_delta;
    std::vector<int> allowed_nodes;
    std::vector<std::vector<double>> eta;
    int current_node;

public:
    Ant(ACO* aco, ACOGraph* g) {
        colony = aco;
        graph = g;
        solution_cost = 0.0;
        solution.clear(); // initializing empty vector with clear
        // init 3D pheremone delta matrix with zeros
        pheromone_delta.resize(graph->n, std::vector<double>(graph->n, 0.0));
        // init allowed nodes empty array of size n
        allowed_nodes.resize(graph->n);
        // fill allowed nodes array with nodes indexes (i)
        for (int i = 0; i < graph->n; i++) {
            allowed_nodes[i] = i;
        }
        // initialize eta 2D array of size n x n with zeros
        eta.resize(graph->n, std::vector<double>(graph->n, 0.0));
        // fill eta array with 1.0 / d_{ij} except the diagonal
        for (int i = 0; i < graph->n; i++) {
            for (int j = 0; j < graph->n; j++) {
                if (i != j) { 
                    eta[i][j] = 1.0 / graph->cost_matrix[i][j]; 
                }
            }
        }
        int starting_node = rand() % graph->n; // starting node (city)
        solution.push_back(starting_node); // starting node is added to solution for this ant solution
        current_node = starting_node; // current node is starting node
        // remove starting node from allowed_nodes: first node (city) is not allowed to be visited again // nodes can be visited just once
        allowed_nodes.erase(std::remove(allowed_nodes.begin(), allowed_nodes.end(), starting_node), allowed_nodes.end());
    }
};
