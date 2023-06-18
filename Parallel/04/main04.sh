#!/bin/bash

NODES=100
EXPERIMENTS=100
SEED=42

for (( np = 31; np <= 33; np += 2 )); do
    echo "Running ./main04 $NODES $EXPERIMENTS $SEED"
    mpirun -np "$np" --oversubscribe ./main04 "$NODES" "$EXPERIMENTS" "$SEED"
done

