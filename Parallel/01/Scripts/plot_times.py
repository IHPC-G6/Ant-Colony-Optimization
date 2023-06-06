import matplotlib.pyplot as plt

num_nodes = list(range(10, 101, 5))
avg_times_00 = [] # unoptimized sequential
avg_times_01 = [] # 1D matrices sequential

for n in num_nodes:
    filename = f"../../00/Times/times_{n}_100.txt"
    with open(filename, "r") as file:
        times = [float(line.strip()) for line in file]
        avg_time = sum(times) / len(times)
        avg_times_00.append(avg_time)

for n in num_nodes:
    filename = f"../Times/times_{n}_100.txt"
    with open(filename, "r") as file:
        times = [float(line.strip()) for line in file]
        avg_time = sum(times) / len(times)
        avg_times_01.append(avg_time)

plt.plot(num_nodes, avg_times_00, marker='o', label='Unoptimized Sequential')
plt.plot(num_nodes, avg_times_01, marker='o', label='1D Matrices Sequential')
plt.xlabel("Number of Nodes [$n$]")
plt.ylabel("Average Time [$s$]")
plt.title("Average Time vs Number of Nodes")
plt.grid(True)
plt.legend()
plt.savefig('../Results/time_vs_nodes_01.pdf')