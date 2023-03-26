# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra

# Define the names of the source files and the output executable
SRCS = main.cpp ACO/ACOGraph.cpp ACO/ACO.cpp ACO/Ant.cpp Utils/GraphConstructor.cpp MST/MST.cpp MST/OneTree.cpp
EXEC = main

# Define the default values for the command line arguments
NODES ?= 20
EXPERIMENTS ?= 100

all:
	# Compile the source files
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC)

run:
	# Run the executable with the specified parameters
	./$(EXEC) $(NODES) $(EXPERIMENTS)

plot:
	# Run the Python script with the specified parameters
	python3 get_results.py $(NODES) $(EXPERIMENTS)
