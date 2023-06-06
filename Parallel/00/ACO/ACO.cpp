#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <memory>

#include "ACOGraph.h"
#include "ACO.h"
#include "Ant.h"

int Q;
float rho;
float beta;
float alpha;
int ant_count;
int iterations;
int update_strategy;

ACO::ACO(int ant_count, int iterations, float alpha, float beta, float rho, int q, int strategy) 
    : Q(q), rho(rho), beta(beta), alpha(alpha), ant_count(ant_count), iterations(iterations), update_strategy(strategy) {}

void ACO::update_pheromone_matrix(ACOGraph* graph, std::vector<std::unique_ptr<Ant>>& ants) {
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

std::pair<std::vector<int>, double> ACO::solve(ACOGraph* graph) {
    double best_cost = std::numeric_limits<double>::infinity();
    std::vector<int> best_solution;
    for (int iter = 0; iter < iterations; iter++) {
        std::vector<std::unique_ptr<Ant>> ants (ant_count);
        for (auto& ant : ants) {
            ant = std::make_unique<Ant>(this, graph);
            for (int i = 0; i < graph->n - 1; i++) {
                ant->select_next_node();
            }
            ant->solution_cost += graph->cost_matrix[ant->solution.back()][ant->solution.front()]; // to close the loop
            if (ant->solution_cost < best_cost) {
                best_cost = ant->solution_cost; // new minimum cost
                best_solution = ant->solution; // new best solution is this ant solution
            }
            // update pheromone delta of each ant
            ant->update_pheromone_delta_matrix();
        }
        // update pheromone matrix at the end of the iteration
        update_pheromone_matrix(graph, ants);
    }
    return { best_solution, best_cost };
}

