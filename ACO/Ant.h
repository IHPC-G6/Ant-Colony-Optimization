#ifndef ANT_H
#define ANT_H

#include "ACO.h"
#include "ACOGraph.h"
#include <vector>
#include <algorithm>
#include <cmath>

class Ant {
    private:
        ACO* colony;
        ACOGraph* graph;           
        std::vector<int> allowed_nodes;
        std::vector<std::vector<double>> eta;
        int current_node;

    public:
        std::vector<std::vector<double>> pheromone_delta_matrix;
        double solution_cost;   
        std::vector<int> solution;
        Ant(ACO* aco, ACOGraph* g);
        int select_next_node();
        void update_pheromone_delta();
};

#endif //ANT_H