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

  cout << "Best path: ";
  for (int i = 0; i < result.first.size(); i++) {
    cout << result.first[i] << " ";
  }
  cout << "\nBest cost: " << result.second << endl;

  double MSTCost = primMST(matrix);

  cout << "MST cost: " << MSTCost << endl; 

  return 0;
}
