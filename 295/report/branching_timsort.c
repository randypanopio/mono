// Enable clock_gettime: https://stackoverflow.com/a/40515669
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "helpers.c"
#include "timsort/timsort.h"
// Comparison function for int64_t
int compareInt64(const void* a, const void* b) {
    int64_t int_a = *(int64_t*)a;
    int64_t int_b = *(int64_t*)b;
    if (int_a < int_b) return -1;
    else if (int_a > int_b) return 1;
    else return 0;
}

void timSort(int64_t arr[], int n) {
    timsort(arr, n, sizeof(int64_t), compareInt64);
}

// test branching behaviours of the timsort algorithm
// 16384, 65536, 1048576, 4194304, 16777216 5 cases
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <type> <size>\n", argv[0]);
        return 1;
    }
    srand(time(NULL));
    char *input1 = argv[1];
    int size = atoi(argv[2]);
    
    if (strcmp(input1, "rev") == 0) { // rev
        int64_t* data = revsorted_array(size);
        timSort(data, size);
        printf("\nCompleted testing type: reverse sorted, size: %u\n", size);
    } else if (strcmp(input1, "sort") == 0) { // sorted
        int64_t* data = sorted_array(size);
        timSort(data, size);
        printf("\nCompleted testing type: sorted, size: %u\n", size);
    } else { // random
        int64_t* data = random_array(size);
        timSort(data, size);
        printf("\nCompleted testing type: random, size: %u\n", size);
    }
    return 0;
}