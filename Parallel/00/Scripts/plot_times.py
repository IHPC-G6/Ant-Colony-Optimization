import matplotlib.pyplot as plt

num_nodes = list(range(10, 101, 5))
avg_times = []

for n in num_nodes:
    filename = f"../Times/times_{n}_100.txt"
    with open(filename, "r") as file:
        times = [float(line.strip()) for line in file]
        avg_time = sum(times) / len(times)
        avg_times.append(avg_time)

plt.plot(num_nodes, avg_times, marker='o')
plt.xlabel("Number of Nodes")
plt.ylabel("Average Time")
plt.title("Average Time vs Number of Nodes")
plt.grid(True)
plt.savefig('../Results/time_vs_nodes_00.pdf')