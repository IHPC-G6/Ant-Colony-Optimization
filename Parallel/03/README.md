This is the MPI version of main02.cpp.

The MPI communication is implemented in the solve function.

A seed is set so that the same graph is generate for all processes. 

Each process is assigned a group of ants. Each group finds their best solution and then they share it to the other groups. A reduce operation is performed to look for the best one (the minimum). Also the pheromones matrices of each group are aggregated with a reduce operation at the end of each iteration. Additionally, the send and recv functions are used to share the best solution path to the root process (0) at the end of each iteration. 

To compile the program, use:

```bash
mpic++ -o main03 main03.cpp -O3 ACO/ACOGraph.cpp ACO/ACO.cpp ACO/Ant.cpp Utils/GraphConstructor.cpp MST/MST.cpp MST/OneTree.cpp
```

To run the experiments use:

``` bash
bash main03.sh np
```
Where np is the number of processes you want to use.