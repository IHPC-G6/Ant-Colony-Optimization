#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " n" << endl;
        return 1;
    }
    int n = atoi(argv[1]);
    cout << n << endl;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { // i+1 to not visit a combination twice
            int num = (i == j) ? 0 : (rand() % 151 + 50);
            cout << i << " " << j << " " << num << endl;
            cout << j << " " << i << " " << num << endl; // we print j, i right away
        }
    }
    return 0;
}
