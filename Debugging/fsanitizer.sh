#!/bin/bash

# Check if input argument is valid
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file_path>"
    exit 1
fi

file_path="$1"

# Address Sanitizer
echo "Compiling with Address Sanitizer ..."
g++ -fsanitize=address -g "$file_path" -o "${file_path%.*}"_asan
echo "Address sanitizer build completed."

# Leak Sanitizer
echo "Compiling with Leak Sanitizer ..."
g++ -fsanitize=leak -g "$file_path" -o "${file_path%.*}"_lsan
echo "Leak sanitizer build completed."

# Undefined Behavior Sanitizer
echo "Compiling with Undefined Behavior Sanitizer ..."
g++ -fsanitize=undefined -g "$file_path" -o "${file_path%.*}"_ubsan
echo "Undefined behavior sanitizer build completed."

# Thread Sanitizer
echo "Compiling with Thread Sanitizer ..."
g++ -fsanitize=thread -g "$file_path" -o "${file_path%.*}"_tsan
echo "Thread sanitizer build completed."

echo "All sanitizers enabled and compiled successfully!"

