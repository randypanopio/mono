import random
import time
import numpy as np

# L1 - 16,384 = 2^14
# L3 - 1,048,576 = 2^20
# Overfit - 16,777,216 = 2^24 = 16777216
sizes = [16384, 1048576, 16777216]
res = ["","",""]

# warmups
for i in range(4):
    SIZE = 1000000
    print("warmup...")
    data = np.array([random.randint(0, SIZE) for _ in range(SIZE)], dtype=np.int64)
    data.sort()

# TEST RANDOM ARRAYS
TYPE = "RANDOM"
RUNCOUNT = 4
for cache, cache_size in enumerate(sizes):
    print(f"running tests on size {cache_size}")
    for run in range(RUNCOUNT):
        # use numpy type cast into 64-bit ints
        # probably not identical to C types but hopefully it is "closer"
        data = np.array([random.randint(0, cache_size) for _ in range(cache_size)], dtype=np.int64)
        # measure only the sort time
        start_time = time.time()
        data.sort() # timsort native
        end_time = time.time()
        run_time = end_time - start_time
        concat = "" if run+1==RUNCOUNT else ", "
        res[cache] += f"{run_time}{concat}"
        print(f"Run {run+1} cache {cache}, results: {run_time} seconds")

print("\n\nresults:\n")
[print(f"[{r}]") for r in res]
print(f"testing {TYPE} arrays complete!")
