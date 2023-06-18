import matplotlib.pyplot as plt
import numpy as np

num_nodes = list(range(10, 101, 5))
avg_times_02 = [] # O3 1D matrices sequential

for n in num_nodes:
    filename = f"../../02/Times/times_{n}_100.txt"
    with open(filename, "r") as file:
        times = [float(line.strip()) for line in file]
        avg_time = sum(times) / len(times)
        avg_times_02.append(avg_time)


num_processes = [2, 4, 8]  
avg_times = {}  # Use a dictionary to store average times for each number of processes

for nnp in num_processes:
    avg_times_np = []  # List to store average times for the current number of processes
    for n in num_nodes:
        filename = f"../Times/times_{n}_100_{nnp}.txt" 
        with open(filename, "r") as file:
            times = [float(line.strip()) for line in file]
            avg_time = sum(times) / len(times)
            print(nnp, n, avg_time)
            avg_times_np.append(avg_time)
    avg_times[nnp] = avg_times_np  # Store the average times for the current number of processes


# theoretical complexity function: number of operations
f = lambda k, n : 25 * k * (n ** 3) + 10 * k * (n ** 2) # if ants = 5n
k = 100

num_ops = []
for n in num_nodes:
    num_ops.append(f(k, n))
num_ops = np.array(num_ops)

# assuming that one operation takes 1e-8 seconds
theoretic = 1e-8 * num_ops

plt.plot(num_nodes, avg_times_02, marker='o', label='O3 1D Matrices Sequential')
plt.plot(num_nodes, theoretic, color='goldenrod', label='Theoretic Sequential (op time: 1e-8s)')

for np in num_processes:
    plt.plot(num_nodes, avg_times[np], marker='o', label=f'O3 1D Matrices Parallel (np={np})')

plt.xlabel("Number of Nodes [$n$]")
plt.ylabel("Average Time [$s$]")
plt.title("Average Time vs Number of Nodes")
plt.grid(True)
plt.legend()
plt.savefig('../Results/time_vs_nodes_03.pdf')