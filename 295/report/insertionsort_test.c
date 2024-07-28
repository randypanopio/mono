// Enable clock_gettime: https://stackoverflow.com/a/40515669
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "helpers.c"

void InsertionSort(int64_t arr[], int n) {
    for (int i = 1; i < n; i++) {
        int64_t key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void warmup() {
    // Warmups
    for (int i = 0; i < 4; i++) {        
        printf("Warmup...\n");
        int64_t* data = random_array(SIZE);
        InsertionSort(data, SIZE);
        free(data);
    }
}

void testRandomArrays(char *res) {
    printf("Testing insertionSort on random arrays\n");
    for (int i = 0; i < RUNCOUNT; i++) {
        int64_t* data = random_array(SIZE);
        
        char* descr = "random insertion";
        double run_time = 0;
        TIMING_RESULT(descr, InsertionSort(data, SIZE), run_time);

        // Append the run time to the result string
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%f%s", run_time, (i + 1 == RUNCOUNT) ? "" : ", ");
        strcat(res, buffer);
        
        // printf("Run %d results: %f ms\n", i + 1, run_time);
        free(data);
    }
    printf("Testing insertion sort on random arrays complete!\n");
}

void testSortedArrays(char *res) {
    printf("Testing insertionSort on sorted arrays\n");
    for (int i = 0; i < RUNCOUNT; i++) {
        int64_t* data = sorted_array(SIZE);
        
        char* descr = "sorted insertion";
        double run_time = 0;
        TIMING_RESULT(descr, InsertionSort(data, SIZE), run_time);

        // Append the run time to the result string
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%f%s", run_time, (i + 1 == RUNCOUNT) ? "" : ", ");
        strcat(res, buffer);
        
        // printf("Run %d results: %f ms\n", i + 1, run_time);
        free(data);
    }
    printf("Testing insertion sort on sorted arrays complete!\n");
    // printf("\nRandom array results:\n[%s]\n", rand_results);
}

void testRevSortedArrays(char *res) {
    printf("Testing insertionSort on reverse sorted arrays\n");
    for (int i = 0; i < RUNCOUNT; i++) {
        int64_t* data = revsorted_array(SIZE);
        
        char* descr = "reverse sorted insertion";
        double run_time = 0;
        TIMING_RESULT(descr, InsertionSort(data, SIZE), run_time);

        // Append the run time to the result string
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%f%s", run_time, (i + 1 == RUNCOUNT) ? "" : ", ");
        strcat(res, buffer);
        free(data);
    }
    printf("Testing insertion sort on reverse sorted arrays complete!\n");
}

int main() {
    srand(time(NULL));
    printf("\nTesting insertion Sort:\n");
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
