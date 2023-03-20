#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "MatrixConstructor.H"
#include "ACO/ACOGraph.h"
#include "ACO/ACO.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " file.txt\n";
    return 1;
  }

  std::string filename(argv[1]);
  std::vector<std::vector<double>> matrix = BuildMatrix(filename);

  ACOGraph graph(matrix);
  ACO aco(10, 100, 0.5, 2.0, 2.5, 0.1, 1.0);

  std::pair<std::vector<int>, double> result = aco.solve(&graph);

  std::cout << "Best path: ";
  for (int i = 0; i < result.first.size(); i++) {
    std::cout << result.first[i] << " ";
  }
  std::cout << "\nBest cost: " << result.second << std::endl;

  return 0;
}
