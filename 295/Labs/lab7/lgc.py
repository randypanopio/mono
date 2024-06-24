# foo

seed = 0
def randint():
    global seed
    seed = seed * 6364136223846793005 + 1442695040888963407
    seed = seed % (2**64)
    return seed

def prod():
    arr1 = [1, 2, 3, 5]
    arr2 = [4, 5, 10, 20]
    ans = 0
    for i in range(4):
        ans += arr1[i] * arr2[i]
    return ans

print(randint())
print("dotproduct: " +str(prod()))

