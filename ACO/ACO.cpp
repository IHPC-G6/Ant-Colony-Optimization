#include <vector>
#include "ACOGraph.h"
#include "Ant.h"

class ACO {
    public:
        int Q;
        float rho;
        float beta;
        float alpha;
        int ant_count;
        int iterations;
        int update_strategy;

        ACO(int ant_count, int iterations, float alpha, float beta, float rho, int q, int strategy) 
            : Q(q), rho(rho), beta(beta), alpha(alpha), ant_count(ant_count), iterations(iterations), update_strategy(strategy) {}

        void update_pheromone_matrix(ACOGraph* graph, std::vector<Ant*> ants) {
            for (int i = 0; i < graph->pheromone_matrix.size(); ++i) {
                for (int j = 0; j < graph->pheromone_matrix[i].size(); ++j) {
                    // see pheromone update formula
                    graph->pheromone_matrix[i][j] *= (1.0 - rho);
                    for (int k = 0; k < ants.size(); ++k) {
                        graph->pheromone_matrix[i][j] += ants[k]->pheromone_delta_matrix[i][j];
                    }
                }
            }
        }
};
