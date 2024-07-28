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

void warmup() {
    // Warmups
    for (int i = 0; i < 4; i++) {        
        printf("Warmup...\n");
        int64_t* data = random_array(SIZE);
        timSort(data, SIZE);
        free(data);
    }
}

void testRandomArrays(char *res) {
    printf("Testing timSort on random arrays\n");
    for (int i = 0; i < RUNCOUNT; i++) {
        int64_t* data = random_array(SIZE);
        
        char* descr = "random timsort";
        double run_time = 0;
        TIMING_RESULT(descr, timSort(data, SIZE), run_time);

        // Append the run time to the result string
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%f%s", run_time, (i + 1 == RUNCOUNT) ? "" : ", ");
        strcat(res, buffer);
        
        // printf("Run %d results: %f ms\n", i + 1, run_time);
        free(data);
    }
    printf("Testing timsort sort on random arrays complete!\n");
}

void testSortedArrays(char *res) {
    printf("Testing timSort on sorted arrays\n");
    for (int i = 0; i < RUNCOUNT; i++) {
        int64_t* data = sorted_array(SIZE);
        
        char* descr = "sorted timsort";
        double run_time = 0;
        TIMING_RESULT(descr, timSort(data, SIZE), run_time);

        // Append the run time to the result string
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%f%s", run_time, (i + 1 == RUNCOUNT) ? "" : ", ");
        strcat(res, buffer);
        
        // printf("Run %d results: %f ms\n", i + 1, run_time);
        free(data);
    }
    printf("Testing timsort sort on sorted arrays complete!\n");
    // printf("\nRandom array results:\n[%s]\n", rand_results);
}

void testRevSortedArrays(char *res) {
    printf("Testing timSort on reverse sorted arrays\n");
    for (int i = 0; i < RUNCOUNT; i++) {
        int64_t* data = revsorted_array(SIZE);
        
        char* descr = "reverse sorted timsort";
        double run_time = 0;
        TIMING_RESULT(descr, timSort(data, SIZE), run_time);

        // Append the run time to the result string
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%f%s", run_time, (i + 1 == RUNCOUNT) ? "" : ", ");
        strcat(res, buffer);
        free(data);
    }
    printf("Testing timsort sort on reverse sorted arrays complete!\n");
}

int main() {
    srand(time(NULL));
    printf("\nTesting timsort Sort:\n");
    warmup();    

    // test
    char revprint[2048] = "";
    testRevSortedArrays(revprint);
    char sortprint[2048] = "";
    testSortedArrays(sortprint);
    char randprint[2048] = "";
    testRandomArrays(randprint);
    
    printf("\nSorted array results:\n[%s]\n", sortprint);
    printf("\nRev Sort array results:\n[%s]\n", revprint);   
    printf("\nRandom array results:\n[%s]\n", randprint);  
    return 0;
}