#include "../include/number_sqrt2.h"
#include <stdlib.h>
#include <math.h>

errorCodes limitSqrt2(double epsilon, double* result) {
     if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    double prevValue = -0.5; // x0 =-0.5
    double currentValue = prevValue - (prevValue * prevValue) / 2.0 + 1.0;
    
    int iterations = 0;
    const int MAX_ITERATIONS = 1000;    

    while (fabs(currentValue - prevValue) >= epsilon) {
        prevValue = currentValue;
        currentValue = prevValue - (prevValue * prevValue) / 2.0 + 1.0;
        
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


errorCodes seriesSqrt2(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
        
    int k = 2; // first value of k
    double term = pow(2, pow(2, -k));
    double prevValue = term;
    
    k++;
    term = pow(2, pow(2, -k));
    double currentValue = prevValue * term;
    
    int iterations = 0;
    const int MAX_ITERATIONS = 100;
    
    while (fabs(currentValue - prevValue) >= epsilon) {
        prevValue = currentValue;
        k++;
        
        term = pow(2, pow(2, -k));
        currentValue = prevValue * term;
        
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


errorCodes equationSqrt2(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }

    double left = 1.0;
    double right = 3.0;
    double mid = 0.0;
    
    int iterations = 0;
    const int MAX_ITERATIONS = 1000;

    while (fabs(right - left) >= epsilon) {
        mid = (left + right) / 2.0;
        double square = mid * mid;
        
        if (square - 2.0 > 0) {
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