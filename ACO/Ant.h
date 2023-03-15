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
        double solution_cost;
        std::vector<int> solution;
        std::vector<std::vector<double>> pheromone_delta;
        std::vector<int> allowed_nodes;
        std::vector<std::vector<double>> eta;
        int current_node;

    public:
        Ant(ACO* aco, ACOGraph* g);
        int _select_next();
        void _update_pheromone_delta();
};

#endif //ANT_H