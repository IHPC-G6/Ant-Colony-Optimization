#ifndef ACO_H
#define ACO_H

#include <vector>
#include <memory>

#include "ACOGraph.h"

// forward declaration: cyclic relationship between ACO and Ant
class Ant;

class ACO {
    public:
        int Q;
        float rho;
        float beta;
        float alpha;
        int ant_count;
        int iterations;
        int update_strategy;

        ACO(int ant_count, int iterations, float alpha, float beta, float rho, int q, int strategy);

        void update_pheromone_matrix(ACOGraph* graph, std::vector<std::unique_ptr<Ant>> ants);

        std::pair<std::vector<int>, double> solve(ACOGraph* graph);
};

#endif  // ACO_H
