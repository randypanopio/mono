#include "vectorclass/vectorclass.h"
#include <cmath>

// uses the vectorclass that mults values between two (double) ptr arrays and sums them together 
double dot_double_vc(double* arr1, double* arr2, uint64_t length) {
    Vec4d vec_sum = 0.0;
    for (uint64_t i = 0; i < length; i += 4) {
        Vec4d vec1 = Vec4d().load(arr1 + i); // Load 4 doubles from arr1
        Vec4d vec2 = Vec4d().load(arr2 + i); // Load 4 doubles from arr2
        vec_sum += vec1 * vec2; // mult the two products
    }
    return horizontal_add(vec_sum);
}

// uses the vectorclass that mults values between two (float) ptr arrays and sums them together 
float dot_single_vc(float* arr1, float* arr2, uint64_t length) {
    Vec8f vec_sum = 0.0;
    for (uint64_t i = 0; i < length; i += 8) {
        Vec8f vec1 = Vec8f().load(arr1 + i); // Load 8 floats from arr1
        Vec8f vec2 = Vec8f().load(arr2 + i); // Load 8 floats from arr2
        vec_sum += vec1 * vec2; // Perform dot product
    }
    return horizontal_add(vec_sum);;
}

// poly double
void map_poly_double_vc(double* input, double* output, uint64_t length, double a, double b, double c, double d) {
    Vec4d vec_a = a, vec_b = b, vec_c = c, vec_d = d;

    for (uint64_t i = 0; i < length; i += 4) {
        Vec4d vec_x = Vec4d().load(input + i);  // Load 4 doubles from input
        Vec4d vec_res = vec_a * vec_x;            // a * x
        vec_res += vec_b;                         // a * x + b
        vec_res *= vec_x;                         // (a * x + b) * x
        vec_res += vec_c;                         // (a * x + b) * x + c
        vec_res *= vec_x;                         // ((a * x + b) * x + c) * x
        vec_res += vec_d;                         // ((a * x + b) * x + c) * x + d
        vec_res.store(output + i);             // assign the calc into the output array
    }
}

// poly single
void map_poly_single_vc(float* input, float* output, uint64_t length, float a, float b, float c, float d) {
    Vec8f vec_a = a, vec_b = b, vec_c = c, vec_d = d;
    for (uint64_t i = 0; i < length; i += 8) {
        Vec8f vec_x = Vec8f().load(input + i);
        Vec8f vec_res = vec_a * vec_x;
        vec_res += vec_b;
        vec_res *= vec_x;
        vec_res += vec_c;
        vec_res *= vec_x;
        vec_res += vec_d;
        vec_res.store(output + i);
    }
}