#include<iostream>
#include<fstream>

using namespace std;

int main(){
    int N, x_min, x_max, y_min, y_max;
    cout<<"Input the ammount of nodes you want to generate: ";
    cin>>N;
    do{
        cout<<"\nInput the range [x_min - x_max] you probably would like to generate each node: ";
        cin<<x_min<<x_max;
    }while(x_max - x_min > 0)
    
}
