#ifndef SOLVE_H 
#define SOLVE_H

#include "constants.h"
#include <stdio.h>
#include <stdint.h>

errorCodes analyzeNumber(const char* number, int* outBase, uint64_t* outValue); // find min base and convert into 10CC
errorCodes solve(FILE* input, FILE* output);

#endif