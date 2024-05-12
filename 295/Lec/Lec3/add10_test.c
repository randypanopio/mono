#include <stdint.h>
#include <stdio.h>
#include "add10.h"

int main() {
    int64_t n = 1234;
    int64_t m = add10(n);
    printf("%ld + 10 = %ld\n", n, m);
}