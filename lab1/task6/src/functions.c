#include "../include/functions.h"
#include <stdio.h>
#include <math.h>

double functionA(double x, double epsilon) {
    if (fabs(x - 0.0) < epsilon) {
        return 1.0;
    }

    double numerator = log(1.0 + x);
    return numerator / x;
}

double functionB(double x, double epsilon) {
    (void)epsilon;
    return exp(-(x * x) / 2.0);
}

double functionC(double x, double epsilon) {
    if (fabs(1.0 - x) < epsilon) {
        return -log(epsilon);
    }

    return -log(1.0 - x);
}

double functionD(double x, double epsilon) {
    if (fabs(x - 0.0) < epsilon) {
        return 1.0;
    }

    return pow(x, x);
}

double calculateIntegral(double (*function)(double, double), double epsilon, double a, double b) {
    if (function == NULL) {
        return NAN;
    }
    if (epsilon <= 0.0 || epsilon >= 1.0) {
        return NAN;
    }
    if (b <= a) {
        return NAN;
    }
    if (fabs(b - a) < epsilon) {
        return 0.0;
    }

    const int MAX_ITERATIONS = 1000000;
    const double INITIAL_DIFFERENCE = 1.0e10;

    int n = 1;
    double step = b - a;
    double previousValue = 0.0;
    double currentValue = 0.5 * (function(a, epsilon) + function(b, epsilon)) * step;
    double difference = INITIAL_DIFFERENCE;

    while (difference >= epsilon) {
        previousValue = currentValue;
        n *= 2;
        step = (b - a) / n;
        currentValue = 0.0;

        for (int i = 0; i < n; i++) {
            double leftX = a + i * step;
            double rightX = leftX + step;
            double leftValue = function(leftX, epsilon);
            double rightValue = function(rightX, epsilon);
            
            if (isnan(leftValue) || isnan(rightValue) || isinf(leftValue) || isinf(rightValue)) {
                return NAN;
            }
            
            currentValue += 0.5 * (leftValue + rightValue);
        }
        
        currentValue *= step;
        
        if (n > 1) {
            difference = fabs(currentValue - previousValue);
        } else {
            difference = INITIAL_DIFFERENCE;
        }
        
        if (n > MAX_ITERATIONS) {
            break;
        }
    }

    return currentValue;
}
