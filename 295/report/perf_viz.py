import numpy as np
import matplotlib.pyplot as plt
import textwrap
from matplotlib.ticker import LogLocator

# Data for branch-misses
# branch_miss_sorted_16384 = [2.01, 2, 2]
# branch_miss_sorted_65536 = [1.00]
# branch_miss_sorted_1048576 = [0.04]
# branch_miss_sorted_4194304 = [0.22]
# branch_miss_sorted_16777216 = [0.22]

# branch_miss_reverse_16384 = [2.12]
# branch_miss_reverse_65536 = [1.02]
# branch_miss_reverse_1048576 = [0.19]
# branch_miss_reverse_4194304 = [0.22]
# branch_miss_reverse_16777216 = [0.22]

# branch_miss_random_16384 = [4.75]
# branch_miss_random_65536 = [4.83]
# branch_miss_random_1048576 = [4.87]
# branch_miss_random_4194304 = [4.91]
# branch_miss_random_16777216 = [4.90]

# # Data for LLC-load-misses
# llc_load_misses_sorted_16384 = [35.50]
# llc_load_misses_sorted_65536 = [14.76]
# llc_load_misses_sorted_1048576 = [26.03]
# llc_load_misses_sorted_4194304 = [14.93]
# llc_load_misses_sorted_16777216 = [22.04]

# llc_load_misses_reverse_16384 = [20.27]
# llc_load_misses_reverse_65536 = [12.89]
# llc_load_misses_reverse_1048576 = [9.27]
# llc_load_misses_reverse_4194304 = [15.26]
# llc_load_misses_reverse_16777216 = [22.50]

# llc_load_misses_random_16384 = [32.21]
# llc_load_misses_random_65536 = [10.52]
# llc_load_misses_random_1048576 = [10.91]
# llc_load_misses_random_4194304 = [15.37]
# llc_load_misses_random_16777216 = [17.52]


# sorted 
# c1
branch_miss_sorted_16384 = [2.03,2.03,2.09,2.10,2.05,2.08,2.08,2.03,2.04,2.09]
llc_load_misses_sorted_16384 = [36.30,35.39,19.68,4.06,23.69,13.44,22.08,20.18,46.02,20.47]

# c2 
branch_miss_sorted_65536 = [0.98,0.98,0.98,0.96,0.98,0.99,0.99,1.01,0.97,0.98]
llc_load_misses_sorted_65536 = [34.38,33.01,18.87,14.03,34.10,32.14,16.50,35.08,12.88,16.79]

# c3
branch_miss_sorted_1048576 =  [0.23,0.04,0.20,0.08,0.10,0.04,0.19,0.10,0.18,0.16]
llc_load_misses_sorted_1048576 = [8.33,20.99,10.85,11.29,9.80,25.96,8.21,8.43,7.65,9.17]

# c4
branch_miss_sorted_4194304 = [0.25,0.20,0.19,0.06,0.11,0.19,0.26,0.10,0.13,0.20]
llc_load_misses_sorted_4194304 = [14.47,14.73,17.00,36.47,17.02,11.97,15.54,14.55,14.56,15.40]

# c5
branch_miss_sorted_16777216 =  [0.03,0.13,0.21,0.17,0.18,0.27,0.11,0.30,0.27,0.28]
llc_load_misses_sorted_16777216 = [38.07,19.77,21.91,12.39,20.10,18.78,21.02,18.56,20.25,19.55]

# revsort
# c1
branch_miss_reverse_16384 =  [2.07,2.09,2.08,2.06,2.10,2.08,2.07,2.09,2.10,2.14]
llc_load_misses_reverse_16384 = [20.88,35.42,20.36,22.27,18.32,18.33,10.82,23.05,19.15,35.41]

# c2
branch_miss_reverse_65536 =  [1.00,1.04,1.02,1.03,1.02,1.02,1.02,1.05,1.01,1.02]
llc_load_misses_reverse_65536 = [31.29,15.01,33.52,34.25,31.96,31.75,14.18,33.26,29.41,32.46]

# c3
branch_miss_reverse_1048576 =  [0.10,0.11,0.15,0.17,0.05,0.21,0.10,0.19,0.24,0.23]
llc_load_misses_reverse_1048576 = [8.06,8.05,8.30,7.29,7.41,9.13,8.54,8.22,9.45,9.91]

# c4
branch_miss_reverse_4194304 = [0.24,0.24,0.24,0.21,0.28,0.18,0.25,0.22,0.24,0.25]
llc_load_misses_reverse_4194304 = [16.07,14.03,14.64,13.68,14.00,13.98,15.14,13.00,14.25,15.22]

# c5
branch_miss_reverse_16777216 =  [0.27,0.18,0.27,0.20,0.22,0.25,0.27,0.25,0.04,0.24]
llc_load_misses_reverse_16777216 = [27.06,17.75,18.37,17.69,16.86,18.61,20.51,21.85,22.92,19.54]

# rand
# c1
branch_miss_random_16384 =  [4.77,4.73,4.72,4.75,4.75,4.75,4.76,4.78,4.76,4.79]
llc_load_misses_random_16384 = [20.18,31.94,13.55,32.47,16.70,11.52,31.75,3.60,9.14,18.48]

# c2
branch_miss_random_65536 = [4.84,4.83,4.82,4.84,4.84,4.84,4.84,4.84,4.83,4.82 ]
llc_load_misses_random_65536 = [6.99,6.15,19.57,16.94,16.87,17.42,19.51,17.97,18.51,6.61]

# c3
branch_miss_random_1048576 = [4.87,4.87,4.87,4.89,4.88,4.88,4.88,4.88,4.89,4.89]
llc_load_misses_random_1048576 = [8.94,8.39,9.08,8.28,9.38,8.88,9.28,8.99,9.17,7.65]

# c4
branch_miss_random_4194304 = [4.90,4.88,4.89,4.89,4.89,4.90,4.91,4.90,4.92,4.88]
llc_load_misses_random_4194304 = [12.17,14.03,13.01,13.47,13.08,11.63,12.93,11.63,11.94,12.80]

# c5
branch_miss_random_16777216 = [4.91,4.91,4.91,4.91,4.91,4.90,4.91,4.92,4.91,4.91]
llc_load_misses_random_16777216 = [17.51,17.79,17.56,18.37,18.25,18.63,16.97,17.34,17.72,16.95]

# Function to calculate means and standard deviations
def calculate_stats(data):
    means = [np.mean(d) for d in data]
    std_devs = [np.std(d) for d in data]
    return means, std_devs

# Calculate stats for branch-misses
branch_miss_sorted_means, branch_miss_sorted_devs = calculate_stats(
    [branch_miss_sorted_16384, branch_miss_sorted_65536, branch_miss_sorted_1048576, branch_miss_sorted_4194304, branch_miss_sorted_16777216]
)
branch_miss_reverse_means, branch_miss_reverse_devs = calculate_stats(
    [branch_miss_reverse_16384, branch_miss_reverse_65536, branch_miss_reverse_1048576, branch_miss_reverse_4194304, branch_miss_reverse_16777216]
)
branch_miss_random_means, branch_miss_random_devs = calculate_stats(
    [branch_miss_random_16384, branch_miss_random_65536, branch_miss_random_1048576, branch_miss_random_4194304, branch_miss_random_16777216]
)

# Calculate stats for LLC-load-misses
llc_load_misses_sorted_means, llc_load_misses_sorted_devs = calculate_stats(
    [llc_load_misses_sorted_16384, llc_load_misses_sorted_65536, llc_load_misses_sorted_1048576, llc_load_misses_sorted_4194304, llc_load_misses_sorted_16777216]
)
llc_load_misses_reverse_means, llc_load_misses_reverse_devs = calculate_stats(
    [llc_load_misses_reverse_16384, llc_load_misses_reverse_65536, llc_load_misses_reverse_1048576, llc_load_misses_reverse_4194304, llc_load_misses_reverse_16777216]
)
llc_load_misses_random_means, llc_load_misses_random_devs = calculate_stats(
    [llc_load_misses_random_16384, llc_load_misses_random_65536, llc_load_misses_random_1048576, llc_load_misses_random_4194304, llc_load_misses_random_16777216]
)

c1 = '#F5DD90'
c2 = '#F68E5F'
c3 = '#586BA4'
c4 = '#F76C5E'
c_out = '#664147'
# Plotting function
def plot_graph(means, devs, title, ylabel, output_filename, graph_height):
    labels = ['16384', '65536', '1048576', '4194304', '16777216']
    x = np.arange(len(labels))
    width = 0.25

    fig, ax = plt.subplots(figsize=(10, graph_height))
    ax.set_axisbelow(True)
    ax.yaxis.grid(True, linestyle='solid', linewidth=0.5)
    ax.yaxis.set_major_locator(LogLocator(base=10, numticks=5))

    rects1 = ax.bar(x - width, means[0], width, yerr=devs[0], label='Sorted', color=c1)
    rects2 = ax.bar(x, means[1], width, yerr=devs[1], label='Reverse Sorted', color=c2)
    rects3 = ax.bar(x + width, means[2], width, yerr=devs[2], label='Random', color=c3)

    ax.set_xlabel('Array Size', fontweight='bold')
    ax.set_ylabel(ylabel, fontweight='bold')
    ax.set_title(title)
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.legend()

    ax.margins(y=0.2)

    def autolabel(rects, std_devs):
        for rect, std_dev in zip(rects, std_devs):
            height = rect.get_height()
            label = f'{height:.2f}±{std_dev:.2f}%'
            wrapped_label = '\n'.join(textwrap.wrap(label, width=5))
            ax.annotate(wrapped_label,
                        xy=(rect.get_x() + rect.get_width() / 2, height),
                        xytext=(0, 6),
                        textcoords="offset points",
                        ha='center', va='bottom')

    autolabel(rects1, devs[0])
    autolabel(rects2, devs[1])
    autolabel(rects3, devs[2])

    fig.tight_layout()
    plt.savefig(output_filename)

# Data for plotting
branch_means = [branch_miss_sorted_means, branch_miss_reverse_means, branch_miss_random_means]
branch_devs = [branch_miss_sorted_devs, branch_miss_reverse_devs, branch_miss_random_devs]
cache_means = [llc_load_misses_sorted_means, llc_load_misses_reverse_means, llc_load_misses_random_means]
cache_devs = [llc_load_misses_sorted_devs, llc_load_misses_reverse_devs, llc_load_misses_random_devs]

# Plot graphs
plot_graph(branch_means, branch_devs, 'Branch Misses by Array Type and Size', 'Branch Misses (%)', 'branch_misses.png', 4)
plot_graph(cache_means, cache_devs, 'LLC Load Misses by Array Type and Size', 'LLC Load Misses (%)', 'llc_load_misses.png', 5)
