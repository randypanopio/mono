import numpy as np
import matplotlib.pyplot as plt
import textwrap
from matplotlib.ticker import LogLocator

# branch-misses 
# sorted group
bmiss_sorted_16384 = 2.01
bmiss_sorted_65536 = 1.00
bmiss_sorted_1048576 = 0.04
bmiss_sorted_4194304 = 0.22
bmiss_sorted_16777216 = 0.22
# reverse group
bmiss_reverse_16384 = 2.12
bmiss_reverse_65536 = 1.02
bmiss_reverse_1048576 = 0.19
bmiss_reverse_4194304 = 0.22
bmiss_reverse_16777216 = 0.22
# random group
bmiss_random_16384 = 4.75
bmiss_random_65536 = 4.83
bmiss_random_1048576 = 4.87
bmiss_random_4194304 = 4.91
bmiss_random_16777216 = 4.90

# LLC-load-misses 
# sorted group
cmiss_sorted_16384 = 35.50
cmiss_sorted_65536 = 14.76
cmiss_sorted_1048576 = 26.03
cmiss_sorted_4194304 = 14.93
cmiss_sorted_16777216 = 22.04
# reverse group
cmiss_reverse_16384 = 20.27
cmiss_reverse_65536 = 12.89
cmiss_reverse_1048576 = 9.27
cmiss_reverse_4194304 = 15.26
cmiss_reverse_16777216 = 22.50
# random group
cmiss_random_16384 = 32.21
cmiss_random_65536 = 10.52
cmiss_random_1048576 = 10.91
cmiss_random_4194304 = 15.37
cmiss_random_16777216 = 17.52