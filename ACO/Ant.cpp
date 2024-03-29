#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

#include "ACOGraph.h"
#include "ACO.h"
#include "Ant.h"

ACO* colony;
ACOGraph* graph;
std::vector<int> allowed_nodes;
std::vector<std::vector<double>> eta;
int current_node;

std::vector<std::vector<double>> pheromone_delta_matrix;
double solution_cost;
std::vector<int> solution;

Ant::Ant(ACO* aco, ACOGraph* g) {
    colony = aco;
    graph = g;
    solution_cost = 0.0;
    solution.clear(); // initializing empty vector with clear
    // init 3D pheremone delta matrix with zeros
    pheromone_delta_matrix.resize(graph->n, std::vector<double>(graph->n, 0.0));
    // init allowed nodes empty array of size n
    allowed_nodes.resize(graph->n);
    // fill allowed nodes array with nodes indexes (i)
    for (int i = 0; i < graph->n; i++) {
        allowed_nodes[i] = i;
    }
    // initialize eta 2D array of size n x n with zeros
    eta.resize(graph->n, std::vector<double>(graph->n, 0.0));
    // fill eta array with 1.0 / d_{ij} except the diagonal
    for (int i = 0; i < graph->n; i++) {
        for (int j = 0; j < graph->n; j++) {
            if (i != j) { 
                eta[i][j] = 1.0 / graph->cost_matrix[i][j]; 
            }
        }
    }
    // we generate a seed that depends on both the time and the object memory address
    // now each ant will start in a different node at each execution
    double seed = static_cast<double>(time(0)) + static_cast<double>(reinterpret_cast<uintptr_t>(this));
    srand(seed);
    int starting_node = rand() % graph->n; // starting node (city)
    solution.push_back(starting_node); // starting node is added to solution for this ant solution
    current_node = starting_node; // current node is starting node
    // remove starting node from allowed_nodes: first node (city) is not allowed to be visited again // nodes can be visited just once
    allowed_nodes.erase(remove(allowed_nodes.begin(), allowed_nodes.end(), starting_node), allowed_nodes.end());
}

int Ant::select_next_node() {
    // See edge selection formula
    double denominator = 0;
    for (int i : allowed_nodes) {
        denominator += pow(graph->pheromone_matrix[current_node][i], colony->alpha) * pow(eta[current_node][i], colony->beta);
    }

    std::vector<double> probabilities(graph->n, 0);
    for (int i = 0; i < graph->n; ++i) {
        if (std::find(allowed_nodes.begin(), allowed_nodes.end(), i) != allowed_nodes.end()) {
            probabilities[i] = (pow(graph->pheromone_matrix[current_node][i], colony->alpha) * pow(eta[current_node][i], colony->beta)) / denominator;
        }
    }

    // Select next node by probability roulette
    bool chosen = false;
    double rand_num = ((double) rand() / (RAND_MAX));
    int selected_node = 0;
    for (int i = 0; i < probabilities.size(); ++i) {
        rand_num -= probabilities[i]; // not allowed nodes have p=0, so won't contribute and won't be selected
        if (rand_num < 0) {
            selected_node = i;
            chosen = true;
            break;
        }
    }

    // in case random roulette fails to choose a node, we select an allowed one randomly
    if (!chosen) {
        double seed = static_cast<double>(time(0)) + static_cast<double>(reinterpret_cast<uintptr_t>(this));
        srand(seed);
        int idx = rand() % allowed_nodes.size();
        selected_node = allowed_nodes[idx];
    }

    // Update allowed, solution, ant cost and current city
    allowed_nodes.erase(remove(allowed_nodes.begin(), allowed_nodes.end(), selected_node), allowed_nodes.end());
    solution.push_back(selected_node);
    solution_cost += graph->cost_matrix[current_node][selected_node];
    current_node = selected_node;
    return selected_node;
}

void Ant::update_pheromone_delta_matrix() {
    pheromone_delta_matrix = std::vector<std::vector<double>>(graph->n, std::vector<double>(graph->n, 0.0));
    for (int ii = 1; ii < solution.size(); ++ii) {
        int i = solution[ii - 1];
        int j = solution[ii];

        if (colony->update_strategy == 0) { // ant-cycle system: // wikipedia 
            pheromone_delta_matrix[i][j] = colony->Q / solution_cost;
        }
        else if (colony->update_strategy == 1) { // ant-quality system
            pheromone_delta_matrix[i][j] = colony->Q;
        }
        else if (colony->update_strategy == 2) { // ant-density system
            pheromone_delta_matrix[i][j] = colony->Q / graph->cost_matrix[i][j];
        }
    }
}