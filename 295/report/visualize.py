import numpy as np
import matplotlib.pyplot as plt

# Example run times in seconds for 10 runs
run_times = [0.10, 0.12, 0.11, 0.13, 0.14, 0.12, 0.11, 0.13, 0.10, 0.12]

# Calculate the average and standard deviation
average_time = np.mean(run_times)
std_deviation = np.std(run_times)

# Prepare data for plotting
labels = ['Benchmark']
average_times = [average_time]
std_deviations = [std_deviation]

# Plotting the bar graph with error bars
fig, ax = plt.subplots()
ax.bar(labels, average_times, yerr=std_deviations, capsize=10, color='skyblue')
ax.set_ylabel('Execution Time (seconds)')
ax.set_title('Benchmark Execution Time with Standard Deviation')

# TODO generate these graphs against my runs