This is the MPI version of main02.cpp.

The MPI communication is implemented in the solve function.

To compile the program, use:

```bash
mpic++ -o main03 main03.cpp -O3 ACO/ACOGraph.cpp ACO/ACO.cpp ACO/Ant.cpp Utils/GraphConstructor.cpp MST/MST.cpp MST/OneTree.cpp
```

To run the experiments use:

``` bash
bash main03.sh np
```
Where np is the number of processes you want to use.