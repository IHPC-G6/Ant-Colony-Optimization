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

        void update_pheromone_matrix(ACOGraph* graph, std::vector<Ant> ants) {
            for (int i = 0; i < graph->pheromone_matrix.size(); ++i) {
                for (int j = 0; j < graph->pheromone_matrix[i].size(); ++j) {
                    // see pheromone update formula
                    graph->pheromone_matrix[i][j] *= (1.0 - rho);
                    for (int k = 0; k < ants.size(); ++k) {
                        graph->pheromone_matrix[i][j] += ants[k].pheromone_delta_matrix[i][j];
                    }
                }
            }
        }

        std::pair<std::vector<int>, double> solve(ACOGraph* graph) {
            double best_cost = std::numeric_limits<double>::infinity();
            std::vector<int> best_solution;
            for (int iter = 0; iter < iterations; iter++) {
                std::vector<Ant> ants(ant_count, Ant(this, graph)); // this is ACO instance
                for (Ant ant : ants) {
                    for (int i = 0; i < graph->n - 1; i++) {
                        ant.select_next_node();
                    }
                    ant.solution_cost += graph->cost_matrix[ant.solution.back()][ant.solution.front()]; // to close the loop
                    if (ant.solution_cost < best_cost) {
                        best_cost = ant.solution_cost; // new minimum cost
                        best_solution = ant.solution; // new best solution is this ant solution
                    }
                    // update pheromone delta of each ant
                    ant.update_pheromone_delta();
                }
                // update pheromone matrix at the end of the iteration
                update_pheromone_matrix(graph, ants);
            }
            return { best_solution, best_cost };
        }
};
