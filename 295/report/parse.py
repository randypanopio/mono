import re
import numpy as np

# Function to parse a single run's output
def parse_run(run_text):
    branch_misses = None
    llc_load_misses = None
    
    for line in run_text.split('\n'):
        if "branch-misses" in line:
            branch_misses = float(re.search(r'(\d+\.\d+)%', line).group(1))
        elif "LLC-load-misses" in line:
            llc_load_misses = float(re.search(r'(\d+\.\d+)%', line).group(1))
    
    return branch_misses, llc_load_misses

# Function to parse the entire perf output
def parse_perf_output(perf_output):
    data = {
        "sorted": {16384: [], 65536: [], 1048576: [], 4194304: [], 16777216: []},
        "rev": {16384: [], 65536: [], 1048576: [], 4194304: [], 16777216: []},
        "rand": {16384: [], 65536: [], 1048576: [], 4194304: [], 16777216: []}
    }
    
    current_test = None
    current_size = None
    current_run = []
    
    for line in perf_output.split('\n'):
        if line.startswith("sorted") or line.startswith("rev") or line.startswith("rand"):
            if current_test and current_run and current_size is not None:
                branch_misses, llc_load_misses = parse_run('\n'.join(current_run))
                if branch_misses is not None and llc_load_misses is not None:
                    data[current_test][current_size].append(branch_misses)
                    data[current_test][current_size].append(llc_load_misses)
            
            match = re.match(r"(sorted|rev|rand) (\d+) run \d+", line)
            if match:
                if current_test and current_run and current_size is not None:
                    branch_misses, llc_load_misses = parse_run('\n'.join(current_run))
                    if branch_misses is not None and llc_load_misses is not None:
                        data[current_test][current_size].append(branch_misses)
                        data[current_test][current_size].append(llc_load_misses)
                
                current_test = match.group(1)
                current_size = int(match.group(2))
                current_run = []
        else:
            current_run.append(line)
    
    # Handle the last run
    if current_test and current_run and current_size is not None:
        branch_misses, llc_load_misses = parse_run('\n'.join(current_run))
        if branch_misses is not None and llc_load_misses is not None:
            data[current_test][current_size].append(branch_misses)
            data[current_test][current_size].append(llc_load_misses)
    
    return data

# Function to convert the parsed data to arrays
def convert_to_arrays(data):
    arrays = {
        "branch_miss_sorted_16384": [],
        "branch_miss_sorted_65536": [],
        "branch_miss_sorted_1048576": [],
        "branch_miss_sorted_4194304": [],
        "branch_miss_sorted_16777216": [],
        "branch_miss_reverse_16384": [],
        "branch_miss_reverse_65536": [],
        "branch_miss_reverse_1048576": [],
        "branch_miss_reverse_4194304": [],
        "branch_miss_reverse_16777216": [],
        "branch_miss_random_16384": [],
        "branch_miss_random_65536": [],
        "branch_miss_random_1048576": [],
        "branch_miss_random_4194304": [],
        "branch_miss_random_16777216": [],
        "llc_load_misses_sorted_16384": [],
        "llc_load_misses_sorted_65536": [],
        "llc_load_misses_sorted_1048576": [],
        "llc_load_misses_sorted_4194304": [],
        "llc_load_misses_sorted_16777216": [],
        "llc_load_misses_reverse_16384": [],
        "llc_load_misses_reverse_65536": [],
        "llc_load_misses_reverse_1048576": [],
        "llc_load_misses_reverse_4194304": [],
        "llc_load_misses_reverse_16777216": [],
        "llc_load_misses_random_16384": [],
        "llc_load_misses_random_65536": [],
        "llc_load_misses_random_1048576": [],
        "llc_load_misses_random_4194304": [],
        "llc_load_misses_random_16777216": []
    }
    
    for test_type, sizes in data.items():
        for size, values in sizes.items():
            # Split values into branch misses and LLC load misses
            branch_misses = values[0::2]
            llc_load_misses = values[1::2]
            
            if test_type == "sorted":
                arrays[f"branch_miss_sorted_{size}"] = branch_misses
                arrays[f"llc_load_misses_sorted_{size}"] = llc_load_misses
            elif test_type == "rev":
                arrays[f"branch_miss_reverse_{size}"] = branch_misses
                arrays[f"llc_load_misses_reverse_{size}"] = llc_load_misses
            elif test_type == "rand":
                arrays[f"branch_miss_random_{size}"] = branch_misses
                arrays[f"llc_load_misses_random_{size}"] = llc_load_misses
    
    return arrays

# Function to calculate means and standard deviations
def calculate_stats(data):
    means = [np.mean(d) for d in data]
    std_devs = [np.std(d) for d in data]
    return means, std_devs

# Main script
with open('perf_output.txt', 'r') as file:
    perf_output = file.read()

parsed_data = parse_perf_output(perf_output)
arrays = convert_to_arrays(parsed_data)

# Calculate stats for branch-misses
branch_miss_sorted_means, branch_miss_sorted_devs = calculate_stats([
    arrays["branch_miss_sorted_16384"],
    arrays["branch_miss_sorted_65536"],
    arrays["branch_miss_sorted_1048576"],
    arrays["branch_miss_sorted_4194304"],
    arrays["branch_miss_sorted_16777216"]
])
branch_miss_reverse_means, branch_miss_reverse_devs = calculate_stats([
    arrays["branch_miss_reverse_16384"],
    arrays["branch_miss_reverse_65536"],
    arrays["branch_miss_reverse_1048576"],
    arrays["branch_miss_reverse_4194304"],
    arrays["branch_miss_reverse_16777216"]
])
branch_miss_random_means, branch_miss_random_devs = calculate_stats([
    arrays["branch_miss_random_16384"],
    arrays["branch_miss_random_65536"],
    arrays["branch_miss_random_1048576"],
    arrays["branch_miss_random_4194304"],
    arrays["branch_miss_random_16777216"]
])

# Calculate stats for LLC-load-misses
llc_load_misses_sorted_means, llc_load_misses_sorted_devs = calculate_stats([
    arrays["llc_load_misses_sorted_16384"],
    arrays["llc_load_misses_sorted_65536"],
    arrays["llc_load_misses_sorted_1048576"],
    arrays["llc_load_misses_sorted_4194304"],
    arrays["llc_load_misses_sorted_16777216"]
])
llc_load_misses_reverse_means, llc_load_misses_reverse_devs = calculate_stats([
    arrays["llc_load_misses_reverse_16384"],
    arrays["llc_load_misses_reverse_65536"],
    arrays["llc_load_misses_reverse_1048576"],
    arrays["llc_load_misses_reverse_4194304"],
    arrays["llc_load_misses_reverse_16777216"]
])
llc_load_misses_random_means, llc_load_misses_random_devs = calculate_stats([
    arrays["llc_load_misses_random_16384"],
    arrays["llc_load_misses_random_65536"],
    arrays["llc_load_misses_random_1048576"],
    arrays["llc_load_misses_random_4194304"],
    arrays["llc_load_misses_random_16777216"]
])

# Output the arrays and calculated statistics
print("Branch Misses:")
print("branch_miss_sorted_16384 =", arrays["branch_miss_sorted_16384"])
print("branch_miss_sorted_65536 =", arrays["branch_miss_sorted_65536"])
print("branch_miss_sorted_1048576 =", arrays["branch_miss_sorted_1048576"])
print("branch_miss_sorted_4194304 =", arrays["branch_miss_sorted_4194304"])
print("branch_miss_sorted_16777216 =", arrays["branch_miss_sorted_16777216"])
print("branch_miss_reverse_16384 =", arrays["branch_miss_reverse_16384"])
print("branch_miss_reverse_65536 =", arrays["branch_miss_reverse_65536"])
print("branch_miss_reverse_1048576 =", arrays["branch_miss_reverse_1048576"])
print("branch_miss_reverse_4194304 =", arrays["branch_miss_reverse_4194304"])
print("branch_miss_reverse_16777216 =", arrays["branch_miss_reverse_16777216"])
print("branch_miss_random_16384 =", arrays["branch_miss_random_16384"])
print("branch_miss_random_65536 =", arrays["branch_miss_random_65536"])
print("branch_miss_random_1048576 =", arrays["branch_miss_random_1048576"])
print("branch_miss_random_4194304 =", arrays["branch_miss_random_4194304"])
print("branch_miss_random_16777216 =", arrays["branch_miss_random_16777216"])

print("\nLLC Load Misses:")
print("llc_load_misses_sorted_16384 =", arrays["llc_load_misses_sorted_16384"])
print("llc_load_misses_sorted_65536 =", arrays["llc_load_misses_sorted_65536"])
print("llc_load_misses_sorted_1048576 =", arrays["llc_load_misses_sorted_1048576"])
print("llc_load_misses_sorted_4194304 =", arrays["llc_load_misses_sorted_4194304"])
print("llc_load_misses_sorted_16777216 =", arrays["llc_load_misses_sorted_16777216"])
print("llc_load_misses_reverse_16384 =", arrays["llc_load_misses_reverse_16384"])
print("llc_load_misses_reverse_65536 =", arrays["llc_load_misses_reverse_65536"])
print("llc_load_misses_reverse_1048576 =", arrays["llc_load_misses_reverse_1048576"])
print("llc_load_misses_reverse_4194304 =", arrays["llc_load_misses_reverse_4194304"])
print("llc_load_misses_reverse_16777216 =", arrays["llc_load_misses_reverse_16777216"])
print("llc_load_misses_random_16384 =", arrays["llc_load_misses_random_16384"])
print("llc_load_misses_random_65536 =", arrays["llc_load_misses_random_65536"])
print("llc_load_misses_random_1048576 =", arrays["llc_load_misses_random_1048576"])
print("llc_load_misses_random_4194304 =", arrays["llc_load_misses_random_4194304"])
print("llc_load_misses_random_16777216 =", arrays["llc_load_misses_random_16777216"])
