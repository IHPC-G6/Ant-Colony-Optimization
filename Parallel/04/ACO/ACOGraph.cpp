#include <vector>
#include <math.h>

#include "ACOGraph.h"

std::vector<std::vector<double>> cost_matrix;
int n; // number of rows and columns // number of nodes
std::vector<double> pheromone_matrix;

ACOGraph::ACOGraph(std::vector<double> cost_matrix) 
    : cost_matrix(cost_matrix) {
    this->n = static_cast<int>(std::sqrt(cost_matrix.size()));
    // pheromone matrix will indicate amount of pheromone in each link
    pheromone_matrix.resize(n * n,  1.0 / (n * n));
}