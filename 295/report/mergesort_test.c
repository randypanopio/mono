// Enable clock_gettime: https://stackoverflow.com/a/40515669
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "helpers.c"

// taken from https://www.geeksforgeeks.org/c-program-for-merge-sort/
void merge(int64_t arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int64_t* L = (int64_t*) malloc(n1 * sizeof(int64_t));
    int64_t* R = (int64_t*) malloc(n2 * sizeof(int64_t));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int64_t arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void warmup() {
    // Warmups
    for (int i = 0; i < 4; i++) {        
        printf("Warmup...\n");
        int64_t* data = random_array(SIZE);
        mergeSort(data, 0, SIZE - 1);
        free(data);
    }
}

void testRandomArrays(char *res) {
    printf("Testing mergeSort on random arrays\n");
    for (int i = 0; i < RUNCOUNT; i++) {
        int64_t* data = random_array(SIZE);
        
        char* descr = "random merge";
        double run_time = 0;
        TIMING_RESULT(descr, mergeSort(data, 0, SIZE - 1), run_time);

        // Append the run time to the result string
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%f%s", run_time, (i + 1 == RUNCOUNT) ? "" : ", ");
        strcat(res, buffer);
        
        // printf("Run %d results: %f ms\n", i + 1, run_time);
        free(data);
    }
    printf("Testing merge sort on random arrays complete!\n");
}

void testSortedArrays(char *res) {
    printf("Testing mergeSort on sorted arrays\n");
    for (int i = 0; i < RUNCOUNT; i++) {
        int64_t* data = sorted_array(SIZE);
        
        char* descr = "sorted merge";
        double run_time = 0;
        TIMING_RESULT(descr, mergeSort(data, 0, SIZE - 1), run_time);

        // Append the run time to the result string
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%f%s", run_time, (i + 1 == RUNCOUNT) ? "" : ", ");
        strcat(res, buffer);
        
        // printf("Run %d results: %f ms\n", i + 1, run_time);
        free(data);
    }
    printf("Testing merge sort on sorted arrays complete!\n");
    // printf("\nRandom array results:\n[%s]\n", rand_results);
}

void testRevSortedArrays(char *res) {
    printf("Testing mergeSort on reverse sorted arrays\n");
    for (int i = 0; i < RUNCOUNT; i++) {
        int64_t* data = revsorted_array(SIZE);
        
        char* descr = "reverse sorted merge";
        double run_time = 0;
        TIMING_RESULT(descr, mergeSort(data, 0, SIZE - 1), run_time);

        // Append the run time to the result string
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%f%s", run_time, (i + 1 == RUNCOUNT) ? "" : ", ");
        strcat(res, buffer);
        free(data);
    }
    printf("Testing merge sort on reverse sorted arrays complete!\n");
}

int main() {
    srand(time(NULL));
    printf("\nTesting merge Sort:\n");
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