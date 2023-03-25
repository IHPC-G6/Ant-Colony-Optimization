#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <numeric>
#include <random>
#include "../Utils/GraphConstructor.h"
#include "../ACO/ACO.h"
#include "../MST/MST.h"
#include "../MST/OneTree.h"

using namespace std;

pair<vector<double>, double> random_search(vector<pair<double, double>> param_ranges, int num_iterations, ACOGraph graph) {
    vector<double> best_params;
    double best_objective = numeric_limits<double>::infinity();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < num_iterations; i++) {
        vector<double> params;
        for (int j = 0; j < param_ranges.size(); j++) {
            double range_min = param_ranges[j].first;
            double range_max = param_ranges[j].second;
            std::uniform_real_distribution<> dis(range_min, range_max);
            double param = dis(gen);
            params.push_back(param);
        }

        int ant_count = (int) params[0];
        int iterations = (int) params[1];
        double alpha = params[2];
        double beta = params[3];
        double rho = params[4];
        int q = (int) params[5];
        //int strategy = (int) params[6];

        ACO aco(ant_count, iterations, alpha, beta, rho, q, 0);

        pair<vector<int>, double> result = aco.solve(&graph);

        double objective = result.second;
        
        if (objective < best_objective) {
            best_params = params;
            best_objective = objective;
            /*
            cout << "Partial Best RS Params: ";
            for (int i = 0; i < params.size(); i++) {
              cout << params[i] << " ";
            }
            cout << "\nPartial Best RS Cost: " << objective << endl;
            */
        }
    }
    
    return { best_params, best_objective };
}

int main(int argc, char* argv[]) {

  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " n" << endl;
    return 1;
  }

  int n = atoi(argv[1]);

  FILE *outfile;
  string filename = "random_search_" + to_string(n) + ".txt";
  outfile = fopen(filename.c_str(), "w");

  if (outfile == NULL) {
      cout << "Error opening file." << endl;
      return 1;
  }

  for (int ii = 0; ii < 100; ii++)
  {

    cout << "Graph " << ii << endl;

    pair<vector<vector<double>>, vector<pair<int, int>>> G = BuildGraph(n);

    vector<vector<double>> matrix = G.first;

    /*
    for (int i = 0; i < matrix.size(); i++) {
      for (int j = 0; j < matrix[i].size(); j++) {
          cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
    */

    ACOGraph graph(matrix);

    // Random Search:

    // define the parameter ranges
    vector<pair<double, double>> param_ranges = {
        {n, n * 5}, // ant count
        {0.5 * n, 0.5 * n + 100}, // iterations
        {0.5, 2.0}, // alpha
        {1.0, 5.0}, // beta
        {0.1, 0.9}, // rho
        {1, 11}, // Q
        //{0, 3}, // strategy
    };

    pair<vector<double>, double> randsearch = random_search(param_ranges, 30, graph);
    
    vector<double> params = randsearch.first;
    double rscost = randsearch.second;

    /*
    cout << "Best RS Params: ";
    for (int i = 0; i < params.size(); i++) {
      cout << params[i] << " ";
    }
    cout << "\nBest RS Cost: " << rscost << endl << endl;
    */

    int ant_count = (int) params[0];
    int iterations = (int) params[1];
    double alpha = params[2];
    double beta = params[3];
    double rho = params[4];
    int q = (int) params[5];
    //int strategy = (int) params[6];

    ACO aco(ant_count, iterations, alpha, beta, rho, q, 0);

    double MSTCost = primMST(matrix); // MST Lowest Bound with MST
    double improved_lower_bound = oneTree(matrix); // Improved Lower Bound with 1-Tree

    // Running Experiments

    int runs = 30;

    double best_cost = numeric_limits<double>::infinity();
    vector<double> costs;

    for (int run = 0; run < runs; run ++)
    {
      pair<vector<int>, double> result = aco.solve(&graph);

      // vector<int> path = result.first;  
      double cost = result.second;

      costs.push_back(cost);

      if (cost < best_cost) {
        best_cost = cost;
      }

      /*
      cout << "Best path: ";
      for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
      }

      cout << "\nBest cost: " << cost << endl;  

      cout << "Best RS Cost: " << rscost << endl; 
      cout << "RS Performance Rate: " << cost / rscost << endl; 

      cout << "MST Cost (Lower Bound): " << MSTCost << endl; 
      cout << "MST Performance Rate: " << cost / MSTCost << endl; 

      cout << "Max 1-Tree Cost (Improved Lower Bound): " << improved_lower_bound << endl; 
      cout << "Max 1-Tree Performance Rate: " << cost / improved_lower_bound << endl << endl; 
      */
    }

    // calculate the average
    double sum_cost = accumulate(costs.begin(), costs.end(), 0.0);
    double avg_cost = sum_cost / costs.size();

    // calculate the standard deviation
    double sq_sum = 0.0;
    for (double x : costs) {
        sq_sum += pow(x - avg_cost, 2);
    }
    double std_dev_cost = sqrt(sq_sum / costs.size());

    fprintf(outfile, "%d %d %f %f %f %d %f %f %f %f %f\n", ant_count, iterations, alpha, beta, rho, q, best_cost, avg_cost, std_dev_cost, MSTCost, improved_lower_bound);

    /*
    cout << "BEST PATH: ";
    for (int i = 0; i < best_path.size(); i++) {
      cout << best_path[i] << " ";
    }

    cout << "\nBEST COST: " << best_cost << endl;  

    cout << "BEST RS COST: " << rscost << endl; 
    cout << "BEST RS PERFORMANCE RATE: " << best_cost / rscost << endl; 

    cout << "BEST MST COST (LOWER BOUND): " << MSTCost << endl; 
    cout << "BEST MST PERFORMANCE RATE: " << best_cost / MSTCost << endl; 

    cout << "BEST MAX 1-TREE COST (IMPROVED LOWER BOUND): " << improved_lower_bound << endl; 
    cout << "BEST MAX 1-TREE PERFORMANCE RATE: " << best_cost / improved_lower_bound << endl << endl; 
    */
  } 

  fclose(outfile);

  return 0;
}
