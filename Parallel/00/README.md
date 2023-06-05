This is the unoptimized sequential version used in the first part of the prject.

The source files are the same that were used in the first part of the project.

The only difference is the main00.cpp file which is a copy of the original main.cpp file but with fixed parameters.

To compile the program, got o the root folder of the project and run:

```bash
g++ -o main00 main00.cpp ACO/ACOGraph.cpp ACO/ACO.cpp ACO/Ant.cpp Utils/GraphConstructor.cpp MST/MST.cpp MST/OneTree.cpp
```

To run the experiments use from the root folder of the project:

``` bash
bash main00.sh
```
