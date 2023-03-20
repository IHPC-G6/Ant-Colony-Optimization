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
        for (int j = 0; j < n; j++) {
            int num = (i == j) ? 0 : (rand() % 151 + 50);
            cout << i << " " << j << " " << num << endl;
        }
    }
    return 0;
}
