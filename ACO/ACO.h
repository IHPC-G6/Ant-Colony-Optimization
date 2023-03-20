#ifndef ACO_H
#define ACO_H

#include <vector>

class ACOGraph;

class Ant {
    private:
        class ACO* colony;
        class ACOGraph* graph;
        std::vector<int> allowed_nodes;
        std::vector<std::vector<double>> eta;
        int current_node;

    public:
        std::vector<std::vector<double>> pheromone_delta_matrix;
        double solution_cost;
        std::vector<int> solution;

        Ant(class ACO* aco, class ACOGraph* g);

        int select_next_node();

        void update_pheromone_delta();

        void clear();
};

class ACOGraph {
    public:
        std::vector<std::vector<double>> cost_matrix;
        int n;
        std::vector<std::vector<double>> pheromone_matrix;

        ACOGraph(std::vector<std::vector<double>> cost_matrix);

        void clear();
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

        ACO(int ant_count, int iterations, float alpha, float beta, float rho, int q, int strategy);

        void update_pheromone_matrix(ACOGraph* graph, std::vector<Ant> ants);

        std::pair<std::vector<int>, double> solve(ACOGraph* graph);

        void clear();
};

#endif  // ACO_H
