#include "../include/functions.h"
#include <stdlib.h>
#include <math.h>

errorCodes calculateFactorial(int n, double* result) {
    if (result == NULL) {
        return INVALID_ARGUMENT;
    }
    
    if (n < 0) {
        return INVALID_ARGUMENT;
    }

    if (n > 100) {
        return OVERFLOW;
    }

    *result = 1.0;
    for (int i = 1; i <= n; ++i) {
        *result *= i;
        if (*result == INFINITY) {
            return OVERFLOW;
        }
    }
    
    return OK;
}

int* generatePrimes(int count, int* actualCount) {
    if (count <= 0 || actualCount == NULL) {
        return NULL;
    }
    
    int* numbers = malloc(sizeof(int) * count);
    if (numbers == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; ++i) {
        numbers[i] = 0;
    }
    
    for (int i = 2; i < count; ++i) {
        if (numbers[i]) {
            continue;
        }
        for (int j = i + i; j < count; j += i) {
            numbers[j] = 1;
        }
    }
    
    *actualCount = count;
    return numbers;
}