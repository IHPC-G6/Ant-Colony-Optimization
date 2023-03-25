#include "MST.h"

using namespace std;

// Improved Lower Bound with 1-Tree
double oneTree(vector<vector<double>> matrix)
{
    vector<double> one_tree_costs;
    for (int i = 0; i < matrix.size(); i++) {
        vector<vector<double>> new_matrix = matrix;
        new_matrix.erase(new_matrix.begin() + i); // Remove the i-th row    
        for (int j = 0; j < new_matrix.size(); j++) {
            new_matrix[j].erase(new_matrix[j].begin() + i); // Removing the i-th column
        }     
        double mst_cost = primMST(new_matrix); // MST without ith node
        vector<double> row_i = matrix[i]; // costs from ith node to every other node
        row_i.erase(row_i.begin() + i); // diagonal element is excluded since it's 0 always
        nth_element(row_i.begin(), row_i.begin() + 2, row_i.end()); // 2 first indexes correspond to the smallest elements
        double closest_sum = row_i[0] + row_i[1]; // we get the two closest distances to node i 
        mst_cost += closest_sum; // we add this two our mst_cost (1-tree cost)

        one_tree_costs.push_back(mst_cost);
    }

    double improved_lower_bound = *max_element(one_tree_costs.begin(), one_tree_costs.end()); // max mst cost is improved lower bound
    return improved_lower_bound;
}