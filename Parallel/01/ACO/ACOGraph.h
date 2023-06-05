#ifndef ACOGRAPH_H
#define ACOGRAPH_H

#include <vector>

class ACOGraph {
    public:
        std::vector<double> cost_matrix;
        int n;
        std::vector<double> pheromone_matrix;

        ACOGraph(std::vector<double> cost_matrix);
};

#endif /* ACOGRAPH_H */
