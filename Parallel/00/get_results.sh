#!/bin/bash

EXPERIMENTS=100

for (( NODES = 10; NODES <= 100; NODES += 5 )); do
    echo "Running python3 Scripts/get_results.py $NODES $EXPERIMENTS"
    python3 Scripts/get_results.py $NODES $EXPERIMENTS
done
