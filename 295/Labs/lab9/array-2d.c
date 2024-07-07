// Get modern behaviour out of time.h, per https://stackoverflow.com/a/40515669
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

/*
#define DATA_T int64_t
#define DATA_PRINTF "%ld"
#define RAND_EXPR (rand() % 256 - 127)
*/
#define DATA_T double
#define DATA_PRINTF "%g"
#define RAND_EXPR ((double)rand() / RAND_MAX - 0.5)

DATA_T* create_array(uint64_t length) {
    DATA_T* array = (DATA_T*)malloc(length * sizeof(DATA_T));
    if (array == NULL) {
        return NULL;
    }
    for (uint64_t i = 0; i < length; i++) {
        array[i] = RAND_EXPR;
    }
    return array;
}

DATA_T sum_array_row(DATA_T* array, uint64_t width, uint64_t height) {
    double sum = 0.0;
    // inner loop loops thru indices of one column, then outer loop sums the rows (for each column)
    // aka add 1+2+3+4 from example
    for (uint64_t row = 0; row < height; row++) {
        for (uint64_t col = 0; col < width; col++) {
            uint64_t index = row * width + col;
            sum += array[index];
        }
    }
    
    return sum;
}

DATA_T sum_array_col(DATA_T* array, uint64_t width, uint64_t height) {
    double sum = 0.0;
    // inner loop loops thru indices of one row, then outer loop sums the columns (for each row)
    // aka add 1+4+2+5... from example
    for (uint64_t col = 0; col < width; col++) {
        for (uint64_t row = 0; row < height; row++) {
            uint64_t index = row * width + col;
            sum += array[index];
        }
    }
    
    return sum;
}

typedef struct {
    DATA_T result;
    double elapsed_ms;
} time_result;

time_result* time_it(DATA_T(*sum_array)(DATA_T*, uint64_t, uint64_t), DATA_T* array, uint64_t width, uint64_t height) {
    struct timespec start, end;
    time_result* res = (time_result*)malloc(sizeof(time_result));

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    DATA_T total = sum_array(array, width, height);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    res->result = total;
    res->elapsed_ms = elapsed * 1000;
    return res;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Must give array size and height on command line.\n");
        return 1;
    }
    uint64_t n = atol(argv[1]);
    uint64_t h = atol(argv[2]);
    printf("Array size: %lu kB\n", n * sizeof(DATA_T) / 1024);
    
    if ( n % h != 0 ) {
        printf("n not divisible by h\n");
        return 1;
    }

    DATA_T* array = create_array(n);
    if (array == NULL) {
        printf("Couldn't allocate.\n");
        return 2;
    }
    time_result* res;

    uint64_t w = n / h;
    // treat array like it's h*w...
    res = time_it(sum_array_col, array, w, h);
    printf("Calculated " DATA_PRINTF " in %8.2f ms on %lu*%lu array.\n", res->result, res->elapsed_ms, w, h);
    free(res);
    free(array);
    return 0;
}


// int main(int argc, char* argv[]) {
//     if (argc < 2) {
//         printf("Must give number of array elements on command line.\n");
//         return 3;
//     }
//     uint64_t n = atol(argv[1]);
//     printf("Array size: %lukB\n", n * sizeof(DATA_T) / 1024);

//     DATA_T* array = create_array(n);
//     if (array == NULL) {
//         printf("Couldn't allocate array.\n");
//         return 4;
//     }
//     time_result* res;

//     // do some warmups
//     res = time_it(sum_array_row, array, n, 1);
//     free(res);
//     res = time_it(sum_array_col, array, n, 1);
//     free(res);
//     res = time_it(sum_array_row, array, n, 1);
//     free(res);
//     res = time_it(sum_array_col, array, n, 1);
//     free(res);

//     // // original code
//     // for (uint64_t w = 1; w <= n; w++) {
//     //     // try all array widths that divide the size...
//     //     if (n % w == 0) {
//     //         uint64_t h = n / w;
//     //         // treat array like it's h*w...
//     //         res = time_it(sum_array_col, array, w, h);
//     //         //res = time_it(sum_array_row, array, w, h);
//     //         printf("Calculated " DATA_PRINTF " in %8.2fms on %lu*%lu array.\n", res->result, res->elapsed_ms, w, h);
//     //     }
//     // }

//     for (uint64_t w = 1; w <= n; w++) {
//         // try all array widths that divide the size...
//         if (n % w == 0) {
//             uint64_t h = n / w;
//             // treat array like it's h*w...
//             res = time_it(sum_array_col, array, w, h);
//             printf("Col Calculated " DATA_PRINTF " in %8.2fms on w:%lu*h:%lu array.\n", res->result, res->elapsed_ms, w, h);
//             free(res);
//             //res = time_it(sum_array_row, array, w, h);
//             // res = time_it(sum_array_row, array, w, h);
//             // printf("Row Calculated " DATA_PRINTF " in %8.2fms on w:%lu*h:%lu array.\n", res->result, res->elapsed_ms, w, h);
//             // free(res);
//         }
//     }
//     printf("--------\n");
//     // do separate run for row calc
//     for (uint64_t w = 1; w <= n; w++) {
//         // try all array widths that divide the size...
//         if (n % w == 0) {
//             uint64_t h = n / w;
//             // treat array like it's h*w...
//             // res = time_it(sum_array_col, array, w, h);
//             // printf("Col Calculated " DATA_PRINTF " in %8.2fms on w:%lu*h:%lu array.\n", res->result, res->elapsed_ms, w, h);
//             // free(res);
//             //res = time_it(sum_array_row, array, w, h);
//             res = time_it(sum_array_row, array, w, h);
//             printf("Row Calculated " DATA_PRINTF " in %8.2fms on w:%lu*h:%lu array.\n", res->result, res->elapsed_ms, w, h);
//             free(res);
//         }
//     }

//     printf("--------\n");
    
//     free(array);
//     return 0;
// }

