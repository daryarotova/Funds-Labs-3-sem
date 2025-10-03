#include "../include/primes.h"
#include <stdlib.h>
#include <math.h>

static int isPrime(const int number) { // auxiliary function - checking whether a number is prime
    if (number < 2) {
        return 0;
    }

    int limit = (int)sqrt((double)number);
    int i = 2;

    while (i <= limit) {
        if (number % i == 0) {
            return 0;
        }
        i = i + 1;
    }

    return 1;
}

errorCodes nThPrime(const size_t n, int *primeOut) { // main function - finding the nth prime number
    if (primeOut == NULL) {
        return INVALID_ARGUMENT;
    }

    if (n == 0) {
        return INVALID_ARGUMENT;
    }

    size_t count = 0;
    int candidate = 1;

    while (count < n) {
        candidate = candidate + 1;

        if (isPrime(candidate)) {
            count = count + 1;
        }
    }

    *primeOut = candidate;
    return OK;
}
