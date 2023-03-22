// https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/

// A C++ program for Prim's Minimum
// Spanning Tree (MST) algorithm. The program is
// for adjacency matrix representation of the graph
 
#include <bits/stdc++.h>
using namespace std;
 
// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(double key[], bool mstSet[], int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
 
    return min_index;
}
 
// A utility function to print the
// constructed MST stored in parent[]
void printMST(double parent[], std::vector<std::vector<double>> graph)
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < graph.size(); i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[i][parent[i]] << " \n";
}
 
// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
double primMST(std::vector<std::vector<double>> graph)
{
    // Array to store constructed MST
    double parent[graph.size()];
 
    // Key values used to pick minimum weight edge in cut
    double key[graph.size()];
 
    // To represent set of vertices included in MST
    bool mstSet[graph.size()];
 
    // Initialize all keys as INFINITE
    for (int i = 0; i < graph.size(); i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first
    // vertex.
    key[0] = 0;
   
    // First node is always root of MST
    parent[0] = -1;
 
    // The MST will have V vertices
    for (int count = 0; count < graph.size() - 1; count++) {
         
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet, graph.size());
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < graph.size(); v++)
 
            // graph[u][v] is non zero only for adjacent
            // vertices of m mstSet[v] is false for vertices
            // not yet included in MST Update the key only
            // if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false
                && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
 
    // Print the constructed MST
    //printMST(parent, graph);

    // modified to return cost
    double cost = 0;
    for (int i = 1; i < graph.size(); i++) {
        cost += graph[i][parent[i]];
    }

    return cost;
}