#include<iostream>
#include<fstream>
#include<random>
#include<cmath>


using namespace std;

bool occupied(int i, int j, int **matrix){
    if(matrix[i][j]) return false;
    return true;
}

bool add_point(int x_coordinate, int y_coordinate, int **matrix, int N,int *x_coordinates,int *y_coordinates, int k){
    int i = x_coordinate / N;
    int j = y_coordinate / N;

    if (! occupied(i, j, matrix)){
	x_coordinates[k] = x_coordinate;
	y_coordinates[k] = y_coordinate;
	return true;
    }
    return false;
      
}


int main(){
    int N, x_min, x_max, y_min, y_max, x_radius, y_radius;
    do {cout<<"Input the ammount of nodes you want to generate (one node minimum): ";
    cin>>N;}while(N > 0);
    
    do{
        cout<<"\nInput the range [x_min - x_max] you probably would like to generate each node: ";
        cin<<x_min<<x_max;
	cout>>"\n";
    }while(x_max - x_min > sqrt(N));
    
    do{
        cout<<"\nInput the range [y_min - y_max] you probably would like to generate each node: ";
        cin>>y_min>>y_max;
	cout<<"\n";
    }while(y_max - y_min > sqrt(N));
    
    x_radius = (x_max - x_min) / N;
    y_radius = (y_max - y_min) / N;
    int occupation_matrix[N][N];
    int x_coordinates[N], y_coordinates[N];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> x_gen(x_min, x_max);
    uniform_int_distribution<int> y_gen(y_min, y_max);
    for(int i = 0; i < N; i++){
	for(int j = 0; j < N; j++){
	    occupation_matrix[i][j] = 0;
	}
    }
    int x_coordinate, y_coordinate;
    for (int i = 0; i < N; i++){
	while (true){
	    x_coordinate = x_gen(gen);
	    y_coordinate = y_gen(gen);
	    if (add_point(x_coordinate, y_coordinate, occupation_matrix, N, x_coordinates, y_coordinates, i)) break;
	}
    }




}
