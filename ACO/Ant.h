#ifndef ANT_H
#define ANT_H

#include "ACOGraph.h"
#include "ACO.h"
#include <vector>
#include <algorithm>
#include <cmath>

class ACO;
class ACOGraph;


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
        Ant(ACO* colony, ACOGraph* graph);
        int select_next_node();
        void update_pheromone_delta_matrix();
};

#endif //ANT_H
