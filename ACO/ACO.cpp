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

};
