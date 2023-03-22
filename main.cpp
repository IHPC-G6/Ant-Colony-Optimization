#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Utils/MatrixConstructor.h"
#include "ACO/ACO.h"
#include "MST/MST.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " file.txt\n";
    return 1;
  }

  std::string filename(argv[1]);
  std::vector<std::vector<double>> matrix = BuildMatrix(filename);

  for (int i = 0; i < matrix.size(); i++) {
      for (int j = 0; j < matrix[i].size(); j++) {
          std::cout << matrix[i][j] << " ";
      }
      std::cout << std::endl;
  }

  ACOGraph graph(matrix);
  ACO aco(80, 100, 1.0, 10.0, 0.5, 10, 2);

  std::pair<std::vector<int>, double> result = aco.solve(&graph);

  std::cout << "Best path: ";
  for (int i = 0; i < result.first.size(); i++) {
    std::cout << result.first[i] << " ";
  }
  std::cout << "\nBest cost: " << result.second << std::endl;

  double MSTCost = primMST(matrix);

  std::cout << "MST cost: " << MSTCost << endl; 

  return 0;
}
