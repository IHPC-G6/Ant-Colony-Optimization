#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <memory>
#include <mpi.h>
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
int pid; 
int np;

ACO::ACO(int ant_count, int iterations, float alpha, float beta, float rho, int q, int strategy, int pid, int np) 
    : Q(q), rho(rho), beta(beta), alpha(alpha), ant_count(ant_count), iterations(iterations), update_strategy(strategy), pid(pid), np(np) {}

void ACO::update_pheromone_matrix(ACOGraph* graph, std::vector<std::unique_ptr<Ant>>& ants) {
    for (int i = 0; i < graph->n; ++i) {
        for (int j = 0; j < graph->n; ++j) {
            // see pheromone update formula
            graph->pheromone_matrix[i * graph->n + j] *= (1.0 - rho);
            for (int k = 0; k < ants.size(); ++k) {
                graph->pheromone_matrix[i * graph->n + j] += ants[k]->pheromone_delta_matrix[i * graph->n + j];
            }
        }
    }
}

std::pair<std::vector<int>, double> ACO::solve(ACOGraph* graph) {
    double best_cost = std::numeric_limits<double>::infinity();
    std::vector<int> best_solution;
    graph-> pheromone_matrix.resize(graph -> n * graph -> n , 1.0/(graph->n * graph -> n ) ) ;
    int ant_limit = (ant_count / np) ;
    
    if (ant_count % np < pid) {
        ant_limit += 1; 
    }
    for (int iter = 0; iter < iterations; iter++) {
        
        std::vector<std::unique_ptr<Ant>> ants (ant_limit);

        for (auto& ant : ants) {
            ant = std::make_unique<Ant>(this, graph);
            for (int i = 0; i < graph->n - 1; i++) {
                ant->select_next_node();
            }
            ant->solution_cost += graph->cost_matrix[ant->solution.back() * graph->n + ant->solution.front()]; // to close the loop
            if (ant->solution_cost < best_cost) {
                best_cost = ant->solution_cost; // new minimum cost
                best_solution = ant->solution; // new best solution is this ant solution
            }
            // update pheromone delta of each ant
            ant->update_pheromone_delta_matrix();
        }
        int localres[2] ;
        int globalres[2] ;
        localres[0] = best_cost ; 
        localres[1] = pid ;
        MPI_Allreduce(localres, globalres, 1, MPI_2INTEGER, MPI_MINLOC, MPI_COMM_WORLD);
        best_cost = globalres [ 0 ]; 
        // update pheromone matrix at the end of the iteration
        update_pheromone_matrix(graph, ants);
        std::vector<double> pheromone_matrix_buffer(graph->n*graph->n, 0); // pheromone matrix buffer 
        // all reduce to share pheremone_matrix
        MPI_Allreduce( &graph->pheromone_matrix[0], &pheromone_matrix_buffer[0], graph->n*graph->n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        graph->pheromone_matrix = pheromone_matrix_buffer;
        //std::cout<<globalres[1]<<std::endl;
        if ( pid == 0 ){
            if ( globalres[1] != 0 ){
                MPI_Recv(&best_solution[0], graph->n , MPI_INT , globalres[1] , 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
        else{
            if (pid == globalres[1]) {
                MPI_Send(&best_solution[0], graph->n, MPI_INT, 0, 1, MPI_COMM_WORLD);
            }
        }
    }
    return { best_solution, best_cost };
}
