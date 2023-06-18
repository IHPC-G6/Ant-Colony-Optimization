#!/bin/bash

NODES=100
EXPERIMENTS=100

for (( np = 3; np <= 33; np += 2 )); do
    echo "Running ./main04 $NODES $EXPERIMENTS"
    mpirun -np "$np" --oversubscribe ./main04 "$NODES" "$EXPERIMENTS"
done

