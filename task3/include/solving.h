#ifndef SOLVING_H
#define SOLVING_H

#include "errors.h"

errorCodes solveQuadraticEquation(double epsilon, double a, double b, double c, double *roots); // квадратное уравнение ax^2 + bx + c = 0, результат записывается в roots (должен быть массив размером 2)  
errorCodes isRightTriangle(double epsilon, double sideA, double sideB, double sideC, int *result);

#endif // SOLVING_H