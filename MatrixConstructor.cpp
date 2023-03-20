#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Please specify the input file name." << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream input(filename);
    if (!input.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return 1;
    }

    int n;
    input >> n;
    vector<vector<double>> matrix(n, vector<double>(n));

    int i, j;
    double c;
    while (input >> i >> j >> c) {
        matrix[i][j] = (i == j) ? 0 : c;
    }

    input.close();

    // print matrix
    cout << n << endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << i << " " << j << " " << matrix[i][j] << endl;
        }
    }

    return 0;
}
