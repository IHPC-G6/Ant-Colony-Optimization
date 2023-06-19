import matplotlib.pyplot as plt
import sys

exp = int(sys.argv[1])
nnp = int(sys.argv[2])

# Define the theoretic time function
f = lambda k, n: 25 * k * (n ** 3) + 10 * k * (n ** 2)

def calculate_average_time(file_path):
    with open(file_path, 'r') as file:
        times = [float(line.strip()) for line in file.readlines()]
        average_time = sum(times) / len(times)
        return average_time

def calculate_average_cost(file_path):
    with open(file_path, 'r') as file:
        costs = [float(line.strip()) for line in file.readlines()]
        average_cost = sum(costs) / len(costs)
        return average_cost

def calculate_performance(average_cost, one_tree_cost):
    performance = average_cost / one_tree_cost
    return performance

def calculate_relative_difference(average_time, theoretic_time):
    relative_difference = 1.0 - (average_time / theoretic_time)
    return relative_difference

def generate_plots(exp, nnp):
    nodes = list(range(10, 101, 5))
    performance_values = []
    relative_difference_values = []
    
    for n in nodes:
        times_file = f'../Times/times_{n}_{exp}_{nnp}.txt'
        costs_file = f'../Data/costs/costs_{n}_{exp}_{nnp}.txt'
        graph_file = f'../Data/graphs/graph_{n}_{exp}_{nnp}.txt'
        
        average_time = calculate_average_time(times_file)
        average_cost = calculate_average_cost(costs_file)
        
        with open(graph_file, 'r') as file:
            lines = file.readlines()
            one_tree_cost = float(lines[2].strip())
        
        performance = calculate_performance(average_cost, one_tree_cost)
        relative_difference = calculate_relative_difference(average_time, 1e-8 * f(100, n))
        
        performance_values.append(performance)
        relative_difference_values.append(relative_difference)
    
    # Plot 1: Performance vs. Number of Nodes
    plt.figure(1)
    plt.plot(nodes, performance_values, marker='o', color='goldenrod')
    plt.xlabel('Number of Nodes')
    plt.ylabel('Performance')
    plt.title(f'1-Tree Performance vs. Nodes (exp: {exp}, np: {nnp})')
    plt.grid(True)
    plt.savefig(f'../Results/performance_vs_nodes_{exp}_{nnp}.pdf', format='pdf')
    
    
    # Plot 2: Running Time Relative Difference vs. Number of Nodes
    plt.figure(2)
    plt.plot(nodes, relative_difference_values, marker='o', color='indigo')
    plt.xlabel('Number of Nodes')
    plt.ylabel('Running Time Relative Difference')
    plt.title(f'Running Time Rel. Diff. vs. Nodes (exp: {exp}, np: {nnp})')
    plt.grid(True)
    plt.savefig(f'../Results/time_rel_diff_vs_nodes_{exp}_{nnp}.pdf', format='pdf')
    
    plt.show()

# Call the function to generate the plots
generate_plots(exp, nnp)
