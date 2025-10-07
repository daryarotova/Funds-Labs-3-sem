#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef enum {
    OK = 0,
    INVALID_ARGUMENT = 1,
    OUT_OF_RANGE = 2,
    NO_CONVERGENCE = 3, // несходимость, отсутствие конечного предела
    OVERFLOW = 4,
    MATH_ERROR = 5,
    MEMORY_ERROR = 6
} errorCodes;

#endif