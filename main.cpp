#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Utils/GraphConstructor.h"
#include "ACO/ACO.h"
#include "MST/MST.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " n" << endl;
    return 1;
  }

  int n = atoi(argv[1]);
  pair<vector<vector<double>>, vector<pair<int, int>>> G = BuildGraph(n);

  vector<vector<double>> matrix = G.first;

  for (int i = 0; i < matrix.size(); i++) {
      for (int j = 0; j < matrix[i].size(); j++) {
          cout << matrix[i][j] << " ";
      }
      cout << endl;
  }

  ACOGraph graph(matrix);
  ACO aco(80, 100, 1.0, 10.0, 0.5, 10, 2);

  pair<vector<int>, double> result = aco.solve(&graph);

  vector<int> path = result.first;  
  double cost = result.second;

  cout << "Best path: ";
  for (int i = 0; i < path.size(); i++) {
    cout << path[i] << " ";
  }
  cout << "\nBest cost: " << cost << endl;

  double MSTCost = primMST(matrix);

  cout << "MST Cost (Lower Bound): " << MSTCost << endl; 
  cout << "MST Performance Rate: " << cost / MSTCost << endl; 

  // Improved Lower Bound with 1-Tree
  vector<double> one_tree_costs;
  for (int i = 0; i < matrix.size(); i++) {
      vector<vector<double>> new_matrix = matrix;
      new_matrix.erase(new_matrix.begin() + i); // Remove the i-th row    
      for (int j = 0; j < new_matrix.size(); j++) {
          new_matrix[j].erase(new_matrix[j].begin() + i); // Removing the i-th column
      }     
      double mst_cost = primMST(new_matrix); // MST without ith node
      vector<double> row_i = matrix[i]; // costs from ith node to every other node
      row_i.erase(row_i.begin() + i); // diagonal element is excluded since it's 0 always
      nth_element(row_i.begin(), row_i.begin() + 2, row_i.end()); // 2 first indexes correspond to the smallest elements
      double closest_sum = row_i[0] + row_i[1]; // we get the two closest distances to node i 
      mst_cost += closest_sum; // we add this two our mst_cost (1-tree cost)

      one_tree_costs.push_back(mst_cost);
  }

  double improved_lower_bound = *max_element(one_tree_costs.begin(), one_tree_costs.end()); // max mst cost is improved lower bound

  cout << "Max 1-Tree Cost (Improved Lower Bound): " << improved_lower_bound << endl; 
  cout << "Max 1-Tree Performance Rate: " << cost / improved_lower_bound << endl; 

  return 0;
}
