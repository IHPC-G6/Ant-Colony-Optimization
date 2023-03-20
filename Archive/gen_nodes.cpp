#include<iostream>
#include<fstream>
#include<random>
#include<cmath>
#include<vector>

using namespace std;

bool occupied(int i, int j, const vector<vector<int>>& matrix){
    if(i >= 0 && i < matrix.size() && j >= 0 && j < matrix[i].size() && matrix[i][j]) return false;
    return true;
}

bool add_point(int x_coordinate, int y_coordinate, vector<vector<int>> matrix, int N,int *x_coordinates,int *y_coordinates, int k){
    int i = x_coordinate / N;
    int j = y_coordinate / N;

    if (! occupied(i, j, matrix)){
        x_coordinates[k] = x_coordinate;
        y_coordinates[k] = y_coordinate;
        return true;
    }
    return false;     
}

int main(int argc, char *argv[]){
    int N, x_min, x_max, y_min, y_max;
    if (argc != 5){
        cout << "Usage: ./program_name N x_min x_max y_min y_max" << endl;
        return 1;
    }
    N = atoi(argv[1]);
    x_min = atoi(argv[2]);
    x_max = atoi(argv[3]);
    y_min = atoi(argv[4]);
    y_max = atoi(argv[5]);
    
    int x_radius = (x_max - x_min) / N;
    int y_radius = (y_max - y_min) / N;
    vector<vector<int>> occupation_matrix (N, vector<int>(N));
    int x_coordinates[N], y_coordinates[N];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> x_gen(x_min, x_max);
    uniform_int_distribution<int> y_gen(y_min, y_max);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            occupation_matrix[i][j] = 0;
        }
    }
    int x_coordinate, y_coordinate;
    for (int i = 0; i < N; i++) {
        while (true) {
            x_coordinate = x_gen(gen);
            y_coordinate = y_gen(gen);
            if (add_point(x_coordinate, y_coordinate, occupation_matrix, N, x_coordinates, y_coordinates, i)) {
                break;
            }
        }
    }
}
