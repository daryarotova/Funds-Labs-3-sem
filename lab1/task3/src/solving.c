#include "../include/solving.h"
#include <math.h>
#include <stddef.h>

errorCodes solveQuadraticEquation(double epsilon, double a, double b, double c, double *roots) {
    if (roots == NULL) {
        return INVALID_ARGUMENT;
    }

    if (epsilon <= 0) {
        return INVALID_ARGUMENT;
    }

    if (fabs(a) < epsilon) {
        if (fabs(b) < epsilon) {
            if (fabs(c) < epsilon) {
                roots[0] = INFINITY;
                roots[1] = INFINITY;
                return OK; // бесконечно много решений
            } else {
                roots[0] = NAN;
                roots[1] = NAN;
                return NO_RESULT; // решений нет
            }
        } else {
            double x = -c / b;
            roots[0] = x;
            roots[1] = x;
            return OK; // одно решение
        }
    }

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < -epsilon) {
        roots[0] = NAN;
        roots[1] = NAN;
        return NO_RESULT; // нет действительных корней
    } 
    else if (fabs(discriminant) <= epsilon) {
        double x = -b / (2.0 * a);
        roots[0] = x;
        roots[1] = x;
        return OK; // один корень
    }
    else {
        double sqrtD = sqrt(discriminant);
        if (!isfinite(sqrtD)) {
            roots[0] = NAN;
            roots[1] = NAN;
            return OVERFLOW;
        }
        double x1 = (-b + sqrtD) / (2.0 * a);
        double x2 = (-b - sqrtD) / (2.0 * a);

        if (x2 > x1) {
            double temp = x1;
            x1 = x2;
            x2 = temp;
        }

        roots[0] = x1;
        roots[1] = x2;
        return OK; // два решения
    }
}

errorCodes isRightTriangle(double epsilon, double sideA, double sideB, double sideC, int *result) {
    if (result == NULL) {
        return INVALID_ARGUMENT;
    }

    if (epsilon <= 0) {
        return INVALID_ARGUMENT;
    }

    if (sideA < epsilon || sideB < epsilon || sideC < epsilon) {
        return INVALID_ARGUMENT;
    }

    double maxSide = sideA;
    double other1 = sideB;
    double other2 = sideC;

    if (sideB > maxSide) {
        maxSide = sideB;
        other1 = sideA;
        other2 = sideC;
    }
    if (sideC > maxSide) {
        maxSide = sideC;
        other1 = sideA;
        other2 = sideB;
    }

    double lhs = other1 * other1 + other2 * other2;
    double rhs = maxSide * maxSide;

    if (fabs(lhs - rhs) <= epsilon) {
        *result = 1; // прямоугольный
    } else {
        *result = 0; // не прямоугольный
    }

    return OK;
}
