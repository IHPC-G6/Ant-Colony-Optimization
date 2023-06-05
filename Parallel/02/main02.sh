#!/bin/bash

EXPERIMENTS=100

for (( NODES = 10; NODES <= 100; NODES += 5 )); do
    echo "Running ./main02 $NODES $EXPERIMENTS"
    ./main02 $NODES $EXPERIMENTS
done
