#!/bin/bash

paths="../main.cpp ../ACO/ACOGraph.cpp ../ACO/ACO.cpp ../ACO/Ant.cpp ../Utils/GraphConstructor.cpp ../MST/MST.cpp ../MST/OneTree.cpp"

# Address Sanitizer
echo "Compiling with Address Sanitizer ..."
g++ -fsanitize=address -g $paths -o main_asan
echo "Address sanitizer build completed."

# Leak Sanitizer
echo "Compiling with Leak Sanitizer ..."
g++ -fsanitize=leak -g $paths -o main_lsan
echo "Leak sanitizer build completed."

# Undefined Behavior Sanitizer
echo "Compiling with Undefined Behavior Sanitizer ..."
g++ -fsanitize=undefined -g $paths -o main_ubsan
echo "Undefined behavior sanitizer build completed."

# Thread Sanitizer
echo "Compiling with Thread Sanitizer ..."
g++ -fsanitize=thread -g $paths -o main_tsan
echo "Thread sanitizer build completed."

