#include <stdint.h>

int32_t array_sum(int32_t *arr, uint32_t n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}