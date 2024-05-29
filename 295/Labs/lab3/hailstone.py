def hailstone_length(n):
    length = 0
    while n != 1:
        length += 1
        if (n & 1) == 0:  # if n is even
            n = n // 2    # // is Python integer division
        else:
            n = 3*n + 1
    return length

print("hailstone 1: ")
print(hailstone_length(1))
print("hailstone 5: ")
print(hailstone_length(5))
print("hailstone 20: ")
print(hailstone_length(20))
print("hailstone 123: ")
print(hailstone_length(123))
