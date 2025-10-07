#include "../include/number_pi.h"
#include "../include/functions.h"
#include <stdlib.h>
#include <math.h>

errorCodes limitPi(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    double product = 1.0;
    int n = 1;
    double prevValue = 2.0;
    
    const int MAX_ITERATIONS = 1000000;
    
    while (n < MAX_ITERATIONS) {
        product *= (4.0 * n * n) / (4.0 * n * n - 1.0);
        double currentValue = 2.0 * product;
        
        if (fabs(currentValue - prevValue) < epsilon) {
            *result = currentValue;
            return OK;
        }
        prevValue = currentValue;
        n++;
    }
    
    *result = 2.0 * product;
    return OK;
}

errorCodes seriesPi(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    const int MAX_ITERATIONS = 10000000;
    const int INITIAL_N = 1;
    const double SERIES_MULTIPLIER = 4.0;
    
    int n = INITIAL_N;
    double term = pow(-1, n - 1) / (2.0 * n - 1);
    double prevValue = term;
    
    n++;
    term = pow(-1, n - 1) / (2.0 * n - 1);
    double currentValue = prevValue + term;
    
    int iterations = 0;
    
    while (fabs(SERIES_MULTIPLIER * (currentValue - prevValue)) >= epsilon) {
        prevValue = currentValue;
        n++;
        
        term = pow(-1, n - 1) / (2.0 * n - 1);
        currentValue = prevValue + term;
        
        iterations++;
        if (iterations > MAX_ITERATIONS) {
            *result = SERIES_MULTIPLIER * currentValue;
            return OK;
        }
        
        if (currentValue == INFINITY || currentValue == -INFINITY) {
            return OVERFLOW;
        }
    }
    
    *result = SERIES_MULTIPLIER * currentValue;
    return OK;
}

errorCodes equationPi(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    const int MAX_ITERATIONS = 1000;
    const double INITIAL_VALUE = 3.0;
    const double DERIVATIVE_THRESHOLD = 1e-15;
    
    double value = INITIAL_VALUE;
    double fx = cos(value) + 1.0;
    double fpx = 0.0;
    double delta = 0.0;
    
    int iterations = 0;
    
    while (fabs(fx) >= epsilon) {
        fpx = -sin(value);
        
        if (fabs(fpx) < DERIVATIVE_THRESHOLD) {
            return MATH_ERROR;
        }
        
        delta = fx / fpx;
        value = value - delta;
        
        iterations++;
        if (iterations > MAX_ITERATIONS) {
            return NO_CONVERGENCE;
        }
        
        if (value == INFINITY || value == -INFINITY) {
            return OVERFLOW;
        }
        
        fx = cos(value) + 1.0;
    }
    
    *result = value;
    return OK;
}