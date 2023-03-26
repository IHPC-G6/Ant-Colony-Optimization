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
#include "Utils/GraphConstructor.h"
#include "ACO/ACO.h"
#include "MST/MST.h"
#include "MST/OneTree.h"

using namespace std;

// Define the parameter ranges for each value of n
// each param is a row
// each n is a column: 10, 20, 30, 40, 50
// each pair is range (min, max)
pair<double, double> param_ranges[6][5] = { {{10, 50}, {20, 100}, {140, 150}, {167.80, 182.90}, {150, 225}}, // ant_ount
                                            {{7.00, 16.70}, {10, 110}, {15, 115}, {89.60, 99.40}, {84.40, 94.30}}, // iterations
                                            {{0.5, 2.0}, {0.51, 0.65}, {0.50, 0.65}, {0.51, 0.65}, {0.65, 0.80}}, // alpha
                                            {{4.59, 4.99}, {3.79, 4.19}, {3.48, 3.85}, {4.16, 4.54}, {4.58, 4.96}}, // beta
                                            {{0.3, 0.8}, {0.1, 0.9}, {0.5, 0.8}, {0.1, 0.9}, {0.1, 0.9}}, // rho
                                            {{1, 7}, {1, 11}, {1, 11}, {1, 11}, {4, 9}}}; // Q

// Get index from params ranges matrix based on n
int get_index(int n) {
  if (n <= 10) {
    return 0;
  } else if (n <= 20) {
    return 1;
  } else if (n <= 30) {
    return 2;
  } else if (n <= 40) {
    return 3;
  } else {
    return 4;
  }
}

// get random number in range min, max
double get_random(double min, double max) {
  random_device rd;
  mt19937 gen(time(nullptr));
  uniform_real_distribution<> dis(min, max);
  return dis(gen);
}

int main(int argc, char* argv[]) {

  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " nodes" << " experiments" << endl;
    return 1;
  }

  // Reading Parameter n
  int n = atoi(argv[1]);
  int runs = atoi(argv[2]);

  // Opening files
  FILE *out_graph;
  string f_graph = "Data/graphs/graph_" + to_string(n) + "_" + to_string(runs) + ".txt";
  out_graph = fopen(f_graph.c_str(), "w");

  FILE *out_costs;
  string f_costs = "Data/costs/costs_" + to_string(n) + "_" + to_string(runs) + ".txt";
  out_costs = fopen(f_costs.c_str(), "w");

  FILE *out_paths;
  string f_paths = "Data/paths/paths_" + to_string(n) + "_" + to_string(runs) + ".txt";
  out_paths = fopen(f_paths.c_str(), "w");

  if (out_graph == NULL || out_costs == NULL || out_paths == NULL) {
      cout << "Error opening files." << endl;
      return 1;
  }

  // Constructing graph
  pair<vector<vector<double>>, vector<pair<int, int>>> G = BuildGraph(n);

  vector<vector<double>> matrix = G.first;
  vector<pair<int, int>> points = G.second;

  // Printing Distances Matrix
  /*
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
        cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  */
  
  // Printing Graph Points
  /*
  for (int i = 0; i < points.size(); i++) {
    cout << "(" << points[i].first << ", " << points[i].second << ") ";
  }
  cout << endl;
  */

  // Getting parameters
  int idx = get_index(n);
  int ant_count = (int) get_random(param_ranges[0][idx].first, param_ranges[0][idx].second);
  int iterations = (int) get_random(param_ranges[1][idx].first, param_ranges[1][idx].second);
  double alpha = get_random(param_ranges[2][idx].first, param_ranges[2][idx].second);
  double beta = get_random(param_ranges[3][idx].first, param_ranges[3][idx].second);
  double rho = get_random(param_ranges[4][idx].first, param_ranges[4][idx].second);
  int Q = (int) get_random(param_ranges[5][idx].first, param_ranges[5][idx].second);

  // Preparing ACO
  ACOGraph graph(matrix);
  ACO aco(ant_count, iterations, alpha, beta, rho, Q, 0);

  cout << ant_count << " " << iterations << " " << alpha << " " << beta << " " << rho << " " << Q << endl;

  // Calculating Lower Bounds
  double MSTCost = primMST(matrix); // MST Lowest Bound with MST
  double improved_lower_bound = oneTree(matrix); // Improved Lower Bound with 1-Tree

  // Writing n, lower bounds, params and points to graph file:
  fprintf(out_graph, "%d\n", n);
  fprintf(out_graph, "%f\n", MSTCost);
  fprintf(out_graph, "%f\n", improved_lower_bound);
  fprintf(out_graph, "%d %d %f %f %f %d\n", ant_count, iterations, alpha, beta, rho, Q);
  for (const auto& p : points) {
      fprintf(out_graph, "%d %d\n", p.first, p.second);
  }
  fclose(out_graph);

  // Running Experiments
  for (int i = 0; i < runs; i ++)
  {
    cout << "Experiment " << i << endl;

    pair<vector<int>, double> result = aco.solve(&graph);

    vector<int> path = result.first;  
    double cost = result.second;

    // Printing ACO Path
    /*
    cout << "ACP Path: ";
    for (int i = 0; i < path.size(); i++) {
      cout << path[i] << " ";
    }
    cout << endl;
    */

    cout << "ACO Cost: " << cost << endl;  
    cout << "1-Tree Performance: " << cost / improved_lower_bound << endl;  

    // Writing path to paths file:
    for (const auto& node : path) {
        fprintf(out_paths, "%d ", node);
    }
    fprintf(out_paths, "\n");

    // Writing cost to costs file
    fprintf(out_costs, "%f\n", cost);
  }

  fclose(out_paths);
  fclose(out_costs);

  return 0;
}
