#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits> // include for INT_MAX

using namespace std;

const int MAXN = 1000; // maximum number of vertices
int dist[MAXN][MAXN]; // distance matrix
bool visited[MAXN]; // visited vertices
vector<int> mst[MAXN]; // minimum spanning tree
vector<int> path;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w > other.w; // prioritize smaller edges in the priority queue
    }
};

void prim(int n) {
    priority_queue<Edge> pq;
    pq.push({0, 0, 0}); // start at vertex 0 with weight 0
    while (!pq.empty()) {
        Edge e = pq.top();
        pq.pop();
        if (visited[e.v]) {
            continue; // skip visited vertices
        }
        visited[e.v] = true;
        if (e.u != e.v) {
            mst[e.u].push_back(e.v); // add edge to MST
            mst[e.v].push_back(e.u);
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                pq.push({e.v, i, dist[e.v][i]}); // add adjacent edges to priority queue
            }
        }
    }
}

int dfs(int u, int parent, int& cost, ofstream& fout) {
    fout << u << " "; // write current vertex to output file
    path.push_back(u);
    int min_cost = INT_MAX;
    for (int v : mst[u]) {
        if (v != parent) {
            int subtree_cost = dfs(v, u, cost, fout); // recursively visit adjacent vertices
            if (subtree_cost < min_cost) {
                min_cost = subtree_cost;
            }
        }
    }
    if (min_cost == INT_MAX) {
        min_cost = 0;
    }
    cost += min_cost + dist[u][parent]; // add cost of current edge to parent and minimum cost of subtrees
    return min_cost + dist[u][parent]; // return minimum cost of subtrees and current edge to parent
}



int calcdist(int n){
    int distance=0;
    int prev=0;
    int act=0;
    for(int i = 1; i<n; i++){
        prev=path[i-1];
        act= path[i];
        distance+=dist[prev][act];
    }
    return distance;
}

int calculate_cost(int n) {
    int cost = 0;
    for (int u = 0; u < n; u++) {
        for (int v : mst[u]) {
            cost += dist[u][v];
        }
    }
    return cost / 2; // divide by 2 to account for double counting of edges
}

int main() {
    int n;
    ifstream fin("cost.txt"); // read input from file
    fin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> dist[i][j];
        }
    }
    prim(n);
    ofstream fout("ResultadoMST.txt"); // write output to file
    int cost = 0;
    fout << "Path of MST: ";
    dfs(0, -1, cost, fout); // pass output file stream to DFS function
    fout << endl;
    //fout << "Cost of path: " << cost << endl;
    int weight =0;
    weight= calcdist(n);
    fout<<"Weight of path: "<<weight<<endl;
    for(int i = 0; i<n; i++){
        fout<<i<<": ";
        for(int j : mst[i]){
            fout<<j<<" ";
        }
        fout<<endl;
    }
    fout.close();
    return 0;
}




