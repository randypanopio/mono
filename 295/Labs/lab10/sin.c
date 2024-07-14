// Enable clock_gettime: https://stackoverflow.com/a/40515669
#define _POSIX_C_SOURCE 199309L
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "lab10.h"
#include <math.h>

#define POLYNOMIAL_LENGTH 20000000

#define TIMING_RESULT(DESCR, CODE) do { \
    struct timespec start, end; \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); \
    CODE; \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); \
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; \
    printf("%25s took %7.1f ms\n", descr, elapsed * 1000); \
} while(0)


// test stdlib
void sin_stdlib(double* input, double* output, uint64_t length) {
    for (uint64_t i = 0; i < length; i++) {
        output[i] = sin(input[i]);
    }
}

// std wrap
void test_sin_stdlib() {
    uint64_t length = POLYNOMIAL_LENGTH;
    double* doubles = create_array(length);
    assert(doubles != NULL);
    double* out = (double*)malloc(length * sizeof(double));
    assert(out != NULL);
    char* descr = "sin_stdlib";
    TIMING_RESULT(descr, sin_stdlib(doubles, out, length));
    free(out);
    free(doubles);
}

//warmup
void warmup() {
    uint64_t length = POLYNOMIAL_LENGTH;
    double* doubles = create_array(length);
    assert(doubles != NULL);
    double* out = (double*)malloc(length * sizeof(double));
    assert(out != NULL);

    for (int i = 0; i < 4; i++){
        printf("warmup..");
        sin_stdlib(doubles, out, length);
    }
    printf("\n---- warmup complete ----\n");
    free(out);
    free(doubles);
}

// asm wrap
void test_sin_asm (){ 
    uint64_t length = POLYNOMIAL_LENGTH;
    double* doubles = create_array(length);
    assert(doubles != NULL);
    double* out = (double*)malloc(length * sizeof(double));
    assert(out != NULL);    
    char* descr = "sin_assm";
    TIMING_RESULT(descr, sin_x87(doubles, out, length));
    free(out);
    free(doubles);
}


int main(void) {
    printf("---- Testing sin assembly vs stdlib perf ----\n");
    warmup();
    test_sin_stdlib();
    test_sin_asm();

    return 0;
}

