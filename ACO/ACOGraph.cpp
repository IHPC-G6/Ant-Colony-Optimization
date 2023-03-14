#include <vector>

class ACOGraph {
public:
    std::vector<std::vector<double>> cost_matrix;
    int n; // number of rows and columns // number of nodes
    std::vector<std::vector<double>> pheromone_matrix;

    ACOGraph(std::vector<std::vector<double>> cost_matrix) {
        this->cost_matrix = cost_matrix;
        this->n = cost_matrix.size();
        // pheromone matrix will indicate amount of pheromone in each link
        pheromone_matrix.resize(n, std::vector<double>(n, 1.0 / (n * n)));
    }
};
