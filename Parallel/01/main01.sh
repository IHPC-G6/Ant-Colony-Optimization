#!/bin/bash

EXPERIMENTS=100

for (( NODES = 10; NODES <= 100; NODES += 5 )); do
    echo "Running ./main01 $NODES $EXPERIMENTS"
    ./main01 $NODES $EXPERIMENTS
done
