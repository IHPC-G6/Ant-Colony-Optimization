#!/bin/bash

EXPERIMENTS=100

for (( NODES = 10; NODES <= 100; NODES += 5 )); do
    echo "Running ./main03 $NODES $EXPERIMENTS"
    mpirun -np 4 ./main03 $NODES $EXPERIMENTS
done
