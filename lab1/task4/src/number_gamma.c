#include "../include/number_gamma.h"
#include "../include/functions.h"
#include "../include/number_pi.h"
#include <math.h>
#include <stdlib.h>

errorCodes limitGammaCalc(int m, double* result) {
    if (result == NULL) {
        return INVALID_ARGUMENT;
    }
    
    double summa = 0.0;
    for (int k = 1; k <= m; ++k) {
        double factorialM = 0.0;
        double factorialMK = 0.0;
        double factorialK = 0.0;
        errorCodes status = OK;
        
        status = calculateFactorial(m, &factorialM);
        if (status != OK) {
            return status;
        }
        
        status = calculateFactorial(m - k, &factorialMK);
        if (status != OK) {
            return status;
        }
        
        status = calculateFactorial(k, &factorialK);
        if (status != OK) {
            return status;
        }
        
        double combinations = factorialM / (factorialMK * factorialK);
        double logFactorialK = log(factorialK);
        summa += (combinations * (pow(-1, k) / k)) * logFactorialK;
    }
    
    *result = summa;
    return OK;
}

errorCodes limitGamma(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    int m = 1;
    double prevValue = 0.0;
    double currentValue = 0.0;
    errorCodes status = OK;
    
    status = limitGammaCalc(m++, &prevValue);
    if (status != OK) {
        return status;
    }
    
    status = limitGammaCalc(m++, &currentValue);
    if (status != OK) {
        return status;
    }
    
    while (fabs(currentValue - prevValue) >= epsilon) {
        if (m == 40) {
            break;
        }
        prevValue = currentValue;
        status = limitGammaCalc(m++, &currentValue);
        if (status != OK) {
            *result = currentValue;
            return OK;
        }
    }
    
    *result = currentValue;
    return OK;
}

errorCodes seriesGammaCalc(int k, double* result) {
    if (result == NULL) {
        return INVALID_ARGUMENT;
    }
    
    int sqrtK = sqrt(k);
    *result = (1.0 / (sqrtK * sqrtK)) - (1.0 / k);
    return OK;
}

errorCodes seriesGamma(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    int k = 2;
    double prevPrevValue = 0.0;
    double prevValue = 0.0;
    double currentValue = 0.0;
    double term = 0.0;
    errorCodes status = OK;
    
    status = seriesGammaCalc(k++, &term);
    if (status != OK) {
        return status;
    }
    prevPrevValue = term;
    
    status = seriesGammaCalc(k++, &term);
    if (status != OK) {
        return status;
    }
    prevValue = prevPrevValue + term;
    
    status = seriesGammaCalc(k++, &term);
    if (status != OK) {
        return status;
    }
    currentValue = prevValue + term;
    
    while (fabs(currentValue - prevValue) >= epsilon || fabs(prevValue - prevPrevValue) >= epsilon) {
        prevPrevValue = prevValue;
        prevValue = currentValue;
        
        status = seriesGammaCalc(k++, &term);
        if (status != OK) {
            *result = currentValue;
            return OK;
        }
        
        currentValue = prevValue + term;
    }
    
    double piValue = 0.0;
    status = equationPi(epsilon, &piValue);
    if (status != OK) {
        return status;
    }
    
    double piSquared = piValue * piValue;
    *result = -piSquared / 6.0 + currentValue;
    return OK;
}

errorCodes equationGamma(double epsilon, double* result) {
    if (result == NULL || epsilon <= 0) {
        return INVALID_ARGUMENT;
    }
    
    const int T_MAX = 1000000;
    
    int actualCount = 0;
    int* primeNumbersArray = generatePrimes(T_MAX, &actualCount);
    if (primeNumbersArray == NULL) {
        return MEMORY_ERROR;
    }
    
    double product = 1.0;
    for (int p = 2; p < T_MAX; p++) {
        if (primeNumbersArray[p] == 0) {
            product *= ((double)(p - 1)) / p;
        }
    }
    double resultLimit = log(T_MAX) * product;
    
    free(primeNumbersArray);
    
    if (resultLimit <= 0) {
        return MATH_ERROR;
    }
    
    *result = -log(resultLimit);
    return OK;
}