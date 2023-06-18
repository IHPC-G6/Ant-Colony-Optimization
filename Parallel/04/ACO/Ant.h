#ifndef ANT_H
#define ANT_H

#include "ACOGraph.h"
#include "ACO.h"
#include <vector>
#include <algorithm>
#include <cmath>

class ACO;

class Ant {
    private:
        class ACO* colony;
        class ACOGraph* graph;
        std::vector<int> allowed_nodes;
        std::vector<double> eta;
        int current_node;

    public:
        std::vector<double> pheromone_delta_matrix;
        double solution_cost;
        std::vector<int> solution;

        Ant(ACO* aco, ACOGraph* g);

        int select_next_node();

        void update_pheromone_delta_matrix();
};

#endif //ANT_H
