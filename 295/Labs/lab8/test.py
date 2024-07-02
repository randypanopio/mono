


def sum_array_col(array, width, height):
    total = 0

    return total

def sum_array_row(array, width, height):
    total = 0
    string = "["
    for row in range(height):
        sbs = ""
        for col in range(width):
            index = row * width + col
            val = array[index]
            total += val
            sbs += str(val) +"+"
        string += sbs + "\n"
    print(string+"]")
    return total




arr = [1,2,3,4,5,6]
COL = 3
ROW = 2

print("sum arr col:")
print(sum_array_col(arr,COL,ROW))


print("sum arr row:")
print(sum_array_row(arr,COL,ROW))
