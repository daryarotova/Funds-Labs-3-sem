#ifndef PRIMES_H
#define PRIMES_H

#include <stddef.h>

typedef enum {
    OK = 0,
    INVALID_ARGUMENT,
    MEMORY_ERROR,
    NOT_FOUND
} errorCodes;

errorCodes nThPrime(size_t n, int *primeOut); // the Nth prime number through the prime pointer

#endif // PRIMES_H