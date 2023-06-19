This is the same MPI version as the one found in folder 03.

This 04 folder purpose is to generate the speedup and parallel efficiency plots.

The bash file main04.sh set the number of nodes and experiments to be 100 and then within a for loop it executes the program with different values for np. The range of values is 1, 3, 5, ..., 27, 29.

To compile the program, use:

```bash
mpic++ -o main04 main04.cpp -O3 ACO/ACOGraph.cpp ACO/ACO.cpp ACO/Ant.cpp Utils/GraphConstructor.cpp MST/MST.cpp MST/OneTree.cpp
```

To run the experiments use:

``` bash
bash main04.sh
```