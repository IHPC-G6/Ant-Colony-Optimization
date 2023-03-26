NODES ?= 20
EXPERIMENTS ?= 100

cost_distribution_$(NODES)_$(EXPERIMENTS).pdf cost_scatter_plot_$(NODES)_$(EXPERIMENTS).pdf performance_distribution_$(NODES)_$(EXPERIMENTS).pdf solution_$(NODES)_$(EXPERIMENTS).pdf: Scripts/get_results.py Data/costs/costs_$(NODES)_$(EXPERIMENTS).txt Data/graphs/graph_$(NODES)_$(EXPERIMENTS).txt Data/paths/paths_$(NODES)_$(EXPERIMENTS).txt
	python3 Scripts/get_results.py $(NODES) $(EXPERIMENTS)

Data/costs/costs_$(NODES)_$(EXPERIMENTS).txt Data/graphs/graph_$(NODES)_$(EXPERIMENTS).txt Data/paths/paths_$(NODES)_$(EXPERIMENTS).txt: main
	./main $(NODES) $(EXPERIMENTS)

.PHONY: run
run:
	./main $(NODES) $(EXPERIMENTS)

main: main main.cpp ACO/ACOGraph.cpp ACO/ACO.cpp ACO/Ant.cpp Utils/GraphConstructor.cpp MST/MST.cpp MST/OneTree.cpp
	g++ -o main main.cpp ACO/ACOGraph.cpp ACO/ACO.cpp ACO/Ant.cpp Utils/GraphConstructor.cpp MST/MST.cpp MST/OneTree.cpp
