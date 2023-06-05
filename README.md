# Ant-Colony-Optimization

To compile the unoptimized sequential version, run:

``` bash
g++ -o main main.cpp ACO/ACOGraph.cpp ACO/ACO.cpp ACO/Ant.cpp Utils/GraphConstructor.cpp MST/MST.cpp MST/OneTree.cpp
```

To run the complete flow of this unoptimized sequential version with gmake run:

``` bash
gmake -f makefile.mk NODES={NODES} EXPERIMENTS={EXPERIMENTS}
```

For example:

``` bash
gmake -f makefile.mk NODES=20 EXPERIMENTS=100
```