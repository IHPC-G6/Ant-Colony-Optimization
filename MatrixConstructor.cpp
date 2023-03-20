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