import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import networkx as nx
import sys
#plt.style.use('Solarize_Light2')

n = int(sys.argv[1])
exp = int(sys.argv[2])
nnp = int(sys.argv[3])

avg_time = 0.0
with open(f"Times/times_{n}_{exp}_{nnp}.txt", "r") as file:
    times = [float(line.strip()) for line in file]
    avg_time = sum(times) / len(times)

def plot_cost_dist(aco_costs, one_tree_cost):
    fig, ax = plt.subplots(figsize=(8, 6))
    sns.kdeplot(aco_costs, color='tomato')
    ax.axvline(x=np.mean(aco_costs), color='tomato', linestyle='--', label=f'ACO Cost Mean: ${np.mean(aco_costs):.2f}$')
    ax.axvline(x=one_tree_cost, color='lightseagreen', linestyle='--', label=f'1-Tree Cost: ${one_tree_cost:.2f}$')
    plt.plot([], [], '.', color='white', label=f'ACO Cost STD: ${np.std(aco_costs):.4f}$')
    plt.plot([], [], '.', color='white', label=f'Avg. Running Time: ${avg_time:.2f}s$')
    plt.xlabel('Cost')
    plt.title(f'Cost Distribution Plot: {n} nodes, {exp} experiments, {nnp} processes')
    plt.legend()
    plt.savefig(f'Results/cost_distribution_{n}_{exp}_{nnp}.pdf', format='pdf')

def plot_cost_line(aco_costs, one_tree_cost):
    fig, ax = plt.subplots(figsize=(8, 6))
    plt.plot(aco_costs, '.', color='tomato', label='ACO Cost')
    ax.hlines(y=np.mean(aco_costs), xmin=0, xmax=100, color='tomato', linestyle='-', label=f'ACO Cost Mean: ${np.mean(aco_costs):.2f}$')
    ax.hlines(y=one_tree_cost, xmin=0, xmax=100, color='lightseagreen', linestyle='-', label=f'1-Tree Cost: ${one_tree_cost:.2f}$')
    plt.plot([], [], '.', color='white', label=f'Min. ACO Cost: ${np.min(aco_costs):.2f}$')
    plt.plot([], [], '.', color='white', label=f'Avg. Running Time: ${avg_time:.2f}s$')
    plt.title(f'Cost Scatter Plot: {n} nodes, {exp} experiments, {nnp} processes')
    plt.legend(loc='center right')
    plt.savefig(f'Results/cost_scatter_plot_{n}_{exp}_{nnp}.pdf', format='pdf')

def plot_dist(aco_costs, one_tree_cost):
    fig, ax = plt.subplots(figsize=(8, 6))
    sns.histplot(aco_costs/one_tree_cost, kde=True, bins=10)
    ax.axvline(x=np.mean(aco_costs/one_tree_cost), linestyle='--', label=f'Avg. Performance: ${np.mean(aco_costs/one_tree_cost):.6f}$')
    ax.axvline(x=np.min(aco_costs/one_tree_cost), color='darkmagenta', linestyle='--', label=f'Best Performance: ${np.min(aco_costs/one_tree_cost):.6f}$')
    plt.plot([], [], '.', color='white', label=f'Avg. Running Time: ${avg_time:.2f}s$')
    plt.title(f'1-Tree Performance Distribution: {n} nodes, {exp} experiments, {nnp} processes')
    plt.xlabel('Performance Rate')
    plt.ylabel('Count')
    plt.legend()
    plt.savefig(f'Results/performance_distribution_{n}_{exp}_{nnp}.pdf', format='pdf')

# Open the file for reading
with open(f"Data/graphs/graph_{n}_{exp}_{nnp}.txt", "r") as file:
    # Read the first four lines of the file
    n = int(file.readline())
    mst_cost = float(file.readline())
    one_tree_cost = float(file.readline())
    params = [float(x) for x in file.readline().split()]

    # Create an empty list to store the points
    points = []

    # Read the rest of the lines in the file
    for line in file:
        # Split the line into two coordinates
        x, y = map(float, line.split())
        # Add the coordinates as a tuple to the points list
        points.append((x, y))

aco_costs = []
with open(f'Data/costs/costs_{n}_{exp}_{nnp}.txt', 'r') as f:
    # Read each line and store the numbers in a list
    aco_costs = [float(line.strip()) for line in f]


paths = []

with open(f'Data/paths/paths_{n}_{exp}_{nnp}.txt', 'r') as f:
    # Read each line and split the numbers
    lines = [line.strip().split() for line in f]
    for line in lines:
        edges = []
        for i in range(len(line)-1):
            edges.append((int(line[i]), int(line[i+1])))     
        # Create an edge between the last and first node to close the loop
        edges.append((int(line[-1]), int(line[0])))
        paths.append(edges)

best_path_edges = paths[np.argmin(aco_costs)]

# Convert the list to a numpy array
aco_costs = np.array(aco_costs)

plot_cost_dist(aco_costs, one_tree_cost)
plot_cost_line(aco_costs, one_tree_cost)
plot_dist(aco_costs, one_tree_cost)

distance = lambda p1, p2: np.sqrt((p2[0] - p1[0])**2 + (p2[1] - p1[1])**2)

# Example array of nodes as tuples (x, y)
nodes = points

# Create an empty graph
G = nx.Graph()

# Add nodes to the graph with positions
pos = {}
for i, node in enumerate(nodes):
    G.add_node(i)
    pos[i] = node

# Add edges to create a complete graph
n_nodes = len(nodes)
for i in range(n_nodes):
    for j in range(i+1, n_nodes):
        G.add_edge(i, j)

best_path = nx.DiGraph()
best_path.add_edges_from(best_path_edges)

for u, v in best_path.edges():
    best_path.edges[u, v]['weight'] = distance(points[u], points[v])

best_path_start_node = best_path_edges[0][0]
node_color = ['orangered' if i == best_path_start_node else 'deepskyblue' for i in range(n_nodes)]

# Draw the graph
fig = plt.figure(figsize=(24, 16))
nx.draw_networkx_nodes(G, pos=pos, node_size=800, node_color=node_color, linewidths=0.3, edgecolors='black')
nx.draw_networkx_edges(G, pos, alpha=0.500, edge_color='turquoise')
nx.draw_networkx_edges(best_path, pos=pos, edge_color='crimson', width=2, arrows=True, arrowsize=20)
labels = { i : f'{i}\n{int(p[0]), int(p[1])}' for i, p in enumerate(nodes) }
nx.draw_networkx_labels(G, pos, font_color='black', font_size=10, labels=labels)
edge_labels = nx.get_edge_attributes(best_path, 'weight')
edge_labels = { k : f'{v:.2f}' for k, v in edge_labels.items() }
#nx.draw_networkx_edge_labels(best_path, pos, edge_labels=edge_labels, font_size=8)
plt.title(f'Best Solution for {n} nodes, {exp} experiments, {nnp} processes, Avg. Running Time: {avg_time:.2f}s, Performance: {np.min(aco_costs/one_tree_cost):.6f} \n Parameters: Ant Count={int(params[0])}, Iterations={int(params[1])}, Alpha={params[2]:.2f}, Beta={params[3]:.2f}, Rho={params[4]:.2f}, Q={params[5]}', fontdict={'fontsize': 20})
plt.savefig(f'Results/best_solution_{n}_{exp}_{nnp}.pdf', format='pdf')

# Get the sequence of path nodes
path_nodes = [str(node) for node in best_path.nodes()]
path_sequence = " -> ".join(path_nodes)

# Create the text document
file_name = f'Results/best_solution_path_{n}_{exp}_{nnp}.txt'
with open(file_name, 'w') as file:
    file.write(path_sequence)
