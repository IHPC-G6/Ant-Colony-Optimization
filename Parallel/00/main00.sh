#!/bin/bash

EXPERIMENTS=100

for (( NODES = 75; NODES <= 100; NODES += 5 )); do
    echo "Running ./main00 $NODES $EXPERIMENTS"
    ./main00 $NODES $EXPERIMENTS
done
