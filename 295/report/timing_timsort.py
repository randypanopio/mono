import random
import time
import numpy as np

SIZE = 16384
RUNCOUNT = 32

def random_array(size):
    return np.array([random.randint(0, size) for _ in range(size)], dtype=np.int64)

def revsorted_array(size):
    # randomize a seed to generate offset
    offset = random.randint(size/4, size/2)
    base_array = np.arange(size, 0, -1, dtype=np.int64)
    # Apply offset
    if offset > 0:
        # Ensure offset wraps around using modulo
        offset_array = np.concatenate((base_array[-offset:], base_array[:-offset]))
    else:
        offset_array = base_array
    return offset_array


def sorted_array(size):
    # randomize a seed to generate offset
    offset = random.randint(1, size//2)
    base_array = np.arange(1, size + 1, dtype=np.int64)
    # Apply offset
    if offset > 0:
        # Ensure offset wraps around using modulo
        offset_array = np.concatenate((base_array[-offset:], base_array[:-offset]))
    else:
        offset_array = base_array
    return offset_array

# warmups
for i in range(4):
    print("warmup...")
    data = random_array(SIZE)
    data.sort()

# TEST RANDOM ARRAYS
rand = ""
print("testing random arrays")
for i in range(RUNCOUNT):
    data = random_array(SIZE)
    # measure only the sort time
    start_time = time.time()
    data.sort() # timsort native
    end_time = time.time()
    run_time = (end_time - start_time) * 1000
    concat = "" if i+1==RUNCOUNT else ", "
    rand += f"{run_time}{concat}"
    print(f"Run {i+1} results: {run_time} ms")
print("testing random arrays complete!")

rev = ""
print("testing reverse sorted arrays")
for i in range(RUNCOUNT):
    data = revsorted_array(SIZE)
    # measure only the sort time
    start_time = time.time()
    data.sort() # timsort native
    end_time = time.time()
    run_time = (end_time - start_time) * 1000
    concat = "" if i+1==RUNCOUNT else ", "
    rev += f"{run_time}{concat}"
    print(f"Run {i+1} results: {run_time} ms")
print("testing reverse sorted arrays complete!")

sort = ""
print("testing sorted arrays")
for i in range(RUNCOUNT):
    data = sorted_array(SIZE)
    # measure only the sort time
    start_time = time.time()
    data.sort() # timsort native
    end_time = time.time()
    run_time = (end_time - start_time) * 1000
    concat = "" if i+1==RUNCOUNT else ", "
    sort += f"{run_time}{concat}"
    print(f"Run {i+1} results: {run_time} ms")
print("testing sorted arrays complete!")

print(f"\nreverse sort array results:\n[{rev}]\n")
print(f"sorted array results:\n[{sort}]\n")
print(f"random array results:\n[{rand}]\n")
