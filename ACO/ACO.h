#ifndef ACO_H
#define ACO_H

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
    };

#endif // ACO_H
