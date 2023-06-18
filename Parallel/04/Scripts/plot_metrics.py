import matplotlib.pyplot as plt

# Read data from the files
data = []
num_processes = []
for np in range(1, 31, 2):
    filename = f'../Times/times_100_100_{np}.txt'  # Adjust the filename pattern
    with open(filename, 'r') as file:
        times = [float(line.strip()) for line in file]
        avg_time = sum(times) / len(times)
        data.append((np, avg_time))
        num_processes.append(np)

# Calculate speedup and parallel efficiency
ref_time = data[0][1]  # Time for 1 process (reference)
speedup = [(np, ref_time / time) for np, time in data]
efficiency = [(np, speedup_value / np) for np, speedup_value in speedup]

# Extract data for plotting
np_values, speedup_values = zip(*speedup)
_, efficiency_values = zip(*efficiency)

# Plot speedup
plt.figure()
plt.plot(np_values, speedup_values, 'bo-', label='Real Speedup')
plt.plot(np_values, np_values, '--', color='orange', label='Theretical Speedup')
plt.xlabel('Number of Processes')
plt.ylabel('Speedup')
plt.title('ACO Speedup for $N=100$')
plt.legend()
plt.savefig('S.pdf')

# Plot parallel efficiency
plt.figure()
plt.plot(np_values, efficiency_values, 'ro-')
plt.axhline(y=0.6, color='orange', linestyle='--', label='$60$% Efficiency')
plt.xlabel('Number of Processes')
plt.ylabel('Parallel Efficiency')
plt.title('ACO Parallel Efficiency for $N=100$')
plt.legend()
plt.savefig('E.pdf')

# Show the plots
plt.show()