#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "../Graph/Graph.h"
#include "ACO.h"

class Ant {
private:
    ACO* colony;
    Graph* graph;
    double solution_cost;
    std::vector<int> solution;
    std::vector<std::vector<double>> pheromone_delta;
    std::vector<int> allowed_nodes;
    std::vector<std::vector<double>> eta;
    int current_node;

public:
    Ant(ACO* aco, Graph* g) {
        colony = aco;
        graph = g;
        solution_cost = 0.0;
    }
};
