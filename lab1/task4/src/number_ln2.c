#include "../include/number_ln2.h"
#include <stdlib.h>
#include <math.h>

errorCodes limitLn2(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    const int MAX_ITERATIONS = 1000000;
    const double INITIAL_N = 1.0;
    
    double n = INITIAL_N;
    double currentValue = n * (pow(2, 1.0 / n) - 1.0);
    n += 1.0;
    double prevValue = n * (pow(2, 1.0 / n) - 1.0);
    
    int iterations = 0;
    
    while (fabs(currentValue - prevValue) >= epsilon) {
        prevValue = currentValue;
        n += 1.0;
        currentValue = n * (pow(2, 1.0 / n) - 1.0);
        
        iterations++;
        if (iterations > MAX_ITERATIONS) {
            return NO_CONVERGENCE;
        }
        
        if (currentValue == INFINITY || currentValue == -INFINITY) {
            return OVERFLOW;
        }
    }
    
    *result = currentValue;
    return OK;
}

errorCodes seriesLn2(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    const int MAX_ITERATIONS = 1000000;
    
    double sum = 0.0;
    double term = 1.0;
    int n = 1;
    
    while (n <= MAX_ITERATIONS) {
        term = 1.0 / (n * pow(2, n));
        if (fabs(term) < epsilon) {
            break;
        }
        sum += term;
        n++;
    }
    
    *result = sum;
    return OK;
}

errorCodes equationLn2(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    const int MAX_ITERATIONS = 1000;
    const double LEFT_BOUND = 0.0;
    const double RIGHT_BOUND = 1.0;
    
    double left = LEFT_BOUND;
    double right = RIGHT_BOUND;
    double mid = 0.0;
    
    int iterations = 0;
    
    while (fabs(right - left) >= epsilon) {
        mid = (left + right) / 2.0;
        double expValue = exp(mid);
        
        if (expValue == INFINITY) {
            return OVERFLOW;
        }
        
        if (expValue - 2.0 > 0) {
            right = mid;
        } else {
            left = mid;
        }
        
        iterations++;
        if (iterations > MAX_ITERATIONS) {
            return NO_CONVERGENCE;
        }
    }
    
    *result = (left + right) / 2.0;
    return OK;
}