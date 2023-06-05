In this version, we converted the following matrices to 1D vectors of doubles:

* pheromone_matrix
* pheromone_delta_matrix
* eta
* cost_matrix

The cost matrix corresponds to the actual graph. In main, we created a flattened copy of the 2D matrix and
named it as fmatrix. This is the one that it's being used by ACO Graph and the other modules of the algorithm.

The 2D matrix is still being used by the MST and the OneTree modules to get the lower bounds.

To compile the program, use:

```bash
g++ -o main01 main01.cpp ACO/ACOGraph.cpp ACO/ACO.cpp ACO/Ant.cpp Utils/GraphConstructor.cpp MST/MST.cpp MST/OneTree.cpp
```

To run the experiments use:

``` bash
bash main01.sh
```
