#include "../include/number_e.h"
#include "../include/functions.h"
#include <stdlib.h>
#include <math.h>

errorCodes limitE(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    const int MAX_ITERATIONS = 1000000;
    const double INITIAL_N = 10000.0;
    
    double n = INITIAL_N;
    double currentValue = pow(1.0 + 1.0 / n, n);
    n += 1.0;
    double prevValue = pow(1.0 + 1.0 / n, n);
    
    int iterations = 0;
    
    while (fabs(currentValue - prevValue) >= epsilon) {
        prevValue = currentValue;
        n += 1.0;
        currentValue = pow(1.0 + 1.0 / n, n);
        
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

errorCodes seriesE(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    const int MAX_ITERATIONS = 100;
    
    int n = 0;
    double term = 0.0;
    double factorialValue = 0.0;
    errorCodes status = OK;
    
    status = calculateFactorial(n, &factorialValue);
    if (status != OK) {
        return status;
    }
    
    term = 1.0 / factorialValue;
    double prevValue = term;
    
    n++;
    status = calculateFactorial(n, &factorialValue);
    if (status != OK) {
        return status;
    }
    
    term = 1.0 / factorialValue;
    double currentValue = prevValue + term;
    
    int iterations = 0;
    
    while (fabs(currentValue - prevValue) >= epsilon) {
        prevValue = currentValue;
        n++;
        
        status = calculateFactorial(n, &factorialValue);
        if (status != OK) {
            *result = currentValue;
            return OK;
        }
        
        term = 1.0 / factorialValue;
        currentValue = prevValue + term;
        
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

errorCodes equationE(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    const int MAX_ITERATIONS = 1000;
    const double LEFT_BOUND = 2.0;
    const double RIGHT_BOUND = 4.0;
    
    double left = LEFT_BOUND;
    double right = RIGHT_BOUND;
    double mid = 0.0;
    
    int iterations = 0;
    
    while (fabs(right - left) >= epsilon) {
        mid = (left + right) / 2.0;
        double logValue = log(mid);
        
        if (logValue == INFINITY || logValue == -INFINITY) {
            return MATH_ERROR;
        }
        
        if (logValue - 1.0 > 0) {
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