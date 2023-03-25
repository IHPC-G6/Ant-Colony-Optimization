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

int main(int argc, char* argv[]) {

  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " n" << endl;
    return 1;
  }

  // Reading Parameter n
  int n = atoi(argv[1]);

  // Opening files
  FILE *out_graph;
  string f_graph = "Data/graphs/graph_" + to_string(n) + ".txt";
  out_graph = fopen(f_graph.c_str(), "w");

  FILE *out_costs;
  string f_costs = "Data/costs/costs_" + to_string(n) + ".txt";
  out_costs = fopen(f_costs.c_str(), "w");

  FILE *out_paths;
  string f_paths = "Data/paths/paths_" + to_string(n) + ".txt";
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

  // Preparing ACO
  ACOGraph graph(matrix);
  ACO aco(n, n, 0.8, 2, 0.5, 5, 0);

  // Calculating Lower Bounds
  double MSTCost = primMST(matrix); // MST Lowest Bound with MST
  double improved_lower_bound = oneTree(matrix); // Improved Lower Bound with 1-Tree

  // Writing n, lower bounds and points to graph file:
  fprintf(out_graph, "%d\n", n);
  fprintf(out_graph, "%f\n", MSTCost);
  fprintf(out_graph, "%f\n", improved_lower_bound);
  for (const auto& p : points) {
      fprintf(out_graph, "%d %d\n", p.first, p.second);
  }
  fclose(out_graph);

  // Running Experiments
  for (int i = 0; i < 100; i ++)
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
