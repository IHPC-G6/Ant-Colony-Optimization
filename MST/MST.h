#ifndef PRIM_MST_H
#define PRIM_MST_H

#include <bits/stdc++.h>
using namespace std;

int minKey(double key[], bool mstSet[], int V);
void printMST(double parent[], std::vector<std::vector<double>> graph);
double primMST(std::vector<std::vector<double>> graph);

#endif // PRIM_MST_H
