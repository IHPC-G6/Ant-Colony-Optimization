import numpy as np
import matplotlib.pyplot as plt
import os
plt.style.use('Solarize_Light2')

# Set the directory containing the files
dir_path = './times'

# Define the list of nodes
nodes = [9, 14, 19, 24, 29, 34, 39, 44, 49]

# Initialize the array to hold the average times
avg_times = np.zeros(len(nodes))

# Loop over the files and compute the average time for each node count
for i, node in enumerate(nodes):
    file_path = os.path.join(dir_path, f"times_{node}_100.txt")
    times = np.loadtxt(file_path)
    avg_times[i] = np.mean(times)

# Plot the average times as a function of the number of nodes
plt.plot(nodes, avg_times, 'o-')
plt.xlabel('Number of nodes')
plt.ylabel('Time (seconds)')
plt.title('Average ACO algorithm running time vs. number of nodes')
plt.grid(True)

# Annotate each point with its corresponding x, y values
for x, y in zip(nodes, avg_times):
    label = f"({x}, {y:.2f})"
    plt.annotate(label, (x, y), textcoords="offset points", xytext=(0,10), ha='center')

# Save the plot to a PDF file
plt.savefig('time_vs_nodes.pdf')
