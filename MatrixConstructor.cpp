#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<double>> BuildMatrix(std::string filename) {

    ifstream infile(filename);
    int n;
    infile >> n;

    vector<vector<double>> matrix(n, vector<double>(n));

    int i, j;
    double c;
    while (infile >> i >> j >> c) {
        matrix[i][j] = (i == j) ? 0 : c;
    }

    return matrix;
}

/*
int main(int argc, char *argv[]) {

    if (argc < 2) {
        cout << "Please specify the input file name." << endl;
        return 1;
    }

    string filename = argv[1];
    vector<vector<double>> matrix = BuildMatrix(filename);

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
*/