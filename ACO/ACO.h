#ifndef ACO_H
#define ACO_H

class ACO {
    private:
        void update_pheromone_matrix(ACOGraph* graph, std::vector<Ant> ants);

    public:
        int Q;
        float rho;
        float beta;
        float alpha;
        int ant_count;
        int iterations;
        int update_strategy;

        ACO(int ant_count, int iterations, float alpha, float beta, float rho, int q, int strategy);

        std::pair<std::vector<int>, double> solve(ACOGraph* graph);
    };

#endif // ACO_H
