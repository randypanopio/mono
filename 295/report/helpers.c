// Enable clock_gettime: https://stackoverflow.com/a/40515669
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define RUNCOUNT 32
#define SIZE 65536

#define TIMING_RESULT(DESCR, CODE, TIME_VAR) do { \
    struct timespec start, end; \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); \
    CODE; \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); \
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; \
    TIME_VAR = elapsed * 1000; \
    printf("%25s took %7.1f ms\n", DESCR, elapsed * 1000); \
} while(0)

int64_t* revsorted_array_offset(int size) {
    // Allocate memory for the array
    int64_t* arr = (int64_t*)malloc(size * sizeof(int64_t));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Generate the base reverse sorted array
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }

    // Randomize a seed to generate offset
    int offset = rand() % (size / 4) + (size / 4);

    // Apply the offset
    if (offset > 0) {
        int64_t* temp = (int64_t*)malloc(size * sizeof(int64_t));
        if (!temp) {
            fprintf(stderr, "Memory allocation failed\n");
            free(arr);
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < size; i++) {
            temp[i] = arr[(i + offset) % size];
        }
        memcpy(arr, temp, size * sizeof(int64_t));
        free(temp);
    }

    return arr;
}

int64_t* revsorted_array(int size) {
    // Allocate memory for the array
    int64_t* arr = (int64_t*)malloc(size * sizeof(int64_t));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int seed = rand() % (size / 4) + (size / 4);

    // Generate the base reverse sorted array
    for (int i = 0; i < size; i++) {
        arr[i] = (size - i) * seed;
    }

    return  arr;
}

int64_t* sorted_array(int size) {
    // Allocate memory for the array
    int64_t* arr = (int64_t*)malloc(size * sizeof(int64_t));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int seed = rand() % (size / 2) + 1;
    // Generate the base sorted array
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * seed;
    }
    return arr;
}

int64_t* sorted_array_offset(int size) {
    // Allocate memory for the array
    int64_t* arr = (int64_t*)malloc(size * sizeof(int64_t));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Generate the base sorted array
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    // Randomize a seed to generate offset
    int offset = rand() % (size / 2) + 1;

    // Apply the offset
    if (offset > 0) {
        int64_t* temp = (int64_t*)malloc(size * sizeof(int64_t));
        if (!temp) {
            fprintf(stderr, "Memory allocation failed\n");
            free(arr);
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < size; i++) {
            temp[i] = arr[(i + offset) % size];
        }
        memcpy(arr, temp, size * sizeof(int64_t));
        free(temp);
    }

    return arr;
}

int64_t* random_array(int size) {
    // Allocate memory for the array
    int64_t* arr = (int64_t*)malloc(size * sizeof(int64_t));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Populate the array with random values
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % size;
    }

    return arr;
}
