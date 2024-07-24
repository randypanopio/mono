import time
import numpy as np

SIZE = 1000000
a = np.random.rand(SIZE)
b = np.random.rand(SIZE)

ma = [[1,2,3,4],
    [5,6,7,8],
    [9,10,11,12],
    [13,14,15,16]]
mb = [[2,4,6,8],
      [10,12,14,16],
      [18,20,22,24],
      [26,28,30,32]]

start_time = time.time()
result = np.dot(ma, mb)
end_time = time.time()

list.sort()

print(f"Time taken for np.dot: {end_time - start_time} seconds")
print(f"result: {result}")
