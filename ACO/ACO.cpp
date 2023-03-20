#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>

class ACO;
class ACOGraph;
class Ant;

class ACOGraph {
    public:
        std::vector<std::vector<double>> cost_matrix;
        int n; // number of rows and columns // number of nodes
        std::vector<std::vector<double>> pheromone_matrix;

        ACOGraph(std::vector<std::vector<double>> cost_matrix) 
            : cost_matrix(cost_matrix) {
            this->n = cost_matrix.size();
            // pheromone matrix will indicate amount of pheromone in each link
            pheromone_matrix.resize(n, std::vector<double>(n, 1.0 / (n * n)));
        }
};

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

        Ant(ACO* aco, ACOGraph* g) {
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
            int starting_node = rand() % graph->n; // starting node (city)
            solution.push_back(starting_node); // starting node is added to solution for this ant solution
            current_node = starting_node; // current node is starting node
            // remove starting node from allowed_nodes: first node (city) is not allowed to be visited again // nodes can be visited just once
            allowed_nodes.erase(remove(allowed_nodes.begin(), allowed_nodes.end(), starting_node), allowed_nodes.end());
        }

        int select_next_node() {
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
            int selected_node = 0;
            // Calculate cumulative probabilities
            std::vector<double> cum_probs(probabilities.size(), 0);
            for (int i = 0; i < cum_probs.size(); ++i) {
                cum_probs[i] = (i == 0) ? probabilities[0] : cum_probs[i-1] + probabilities[i];
            }
            // Choose a random number between 0 and the sum of probabilities
            // maybe this can be replaced with just a uniform between 0 and 1 (probs are normalized anyway)
            double rand_num = ((double) rand() / (RAND_MAX)) * cum_probs.back();

            // Find the index of the node whose cumulative probability range
            // contains the random number
            for (int i = 0; i < cum_probs.size(); ++i) {
                if (rand_num <= cum_probs[i]) {
                    selected_node = i;
                    break;
                }
            }
            // Update allowed, solution, ant cost and current city
            allowed_nodes.erase(remove(allowed_nodes.begin(), allowed_nodes.end(), selected_node), allowed_nodes.end());
            solution.push_back(selected_node);
            solution_cost += graph->cost_matrix[current_node][selected_node];
            current_node = selected_node;

            return selected_node;
        }

        void update_pheromone_delta_matrix() {
        pheromone_delta_matrix = std::vector<std::vector<double>>(graph->n, std::vector<double>(graph->n, 0.0));
        for (int ii = 1; ii < solution.size(); ++ii) {
            int i = solution[ii - 1];
            int j = solution[ii];

            if (colony->update_strategy == 1) { // ant-quality system
                pheromone_delta_matrix[i][j] = colony->Q;
            }
            else if (colony->update_strategy == 2) { // ant-density system
                pheromone_delta_matrix[i][j] = colony->Q / graph->cost_matrix[i][j];
            }
            else { // ant-cycle system: // wikipedia 
                pheromone_delta_matrix[i][j] = colony->Q / solution_cost;
            }
        }
    }
};


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
                    ant.update_pheromone_delta_matrix();
                }
                // update pheromone matrix at the end of the iteration
                update_pheromone_matrix(graph, ants);
            }
            return { best_solution, best_cost };
        }
};

