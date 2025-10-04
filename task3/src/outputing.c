#include "../include/outputing.h"
#include <stdio.h>
#include <math.h> // isinf(), isnan()

errorCodes printTableWithInstructions(void) {
    if (printf("./test_lab3.out [flag] [arguments]\n\n") < 0) {
        return IO_ERROR;
    }

    if (printf("Доступные флаги и аргументы:\n") < 0) {
        return IO_ERROR;
    }

    if (printf("-q, /q : четыре вещественных числа (epsilon, a, b, c)\n") < 0) {
        return IO_ERROR;
    }

    if (printf("-m, /m : два целых числа (x, y)\n") < 0) {
        return IO_ERROR;
    }
    
    if (printf("-t, /t : четыре вещественных числа (epsilon, sideA, sideB, sideC)\n\n") < 0) {
        return IO_ERROR;
    }

    return OK;
}

errorCodes printQuadraticSolution(const double *roots, int precision, double a, double b, double c) {
    if (roots == NULL) {
        return INVALID_ARGUMENT;
    }

    if (precision < 0 || precision > 15) {
        return OUT_RANGE; // ограничим точность
    }

    if (printf("Уравнение: (%.*f)x^2 + (%.*f)x + (%.*f) = 0\n", 
               precision, a, precision, b, precision, c) < 0) {
        return IO_ERROR;
    }

    double root1 = roots[0];
    double root2 = roots[1];

    if (isnan(root1)) { // isnan - проверяет, является ли число с плавающей точкой
        if (printf("Корней в действительных числах нет\n\n") < 0) {
            return IO_ERROR;
        }
    } else if (isinf(root1)) { // isninf - проверяет, является ли число бесконечностью
        if (printf("Уравнение имеет бесконечное количество решений\n\n") < 0) {
            return IO_ERROR;
        }
    } else {
        if (printf("Корни: x1 = %.*f, x2 = %.*f\n\n", precision, root1, precision, root2) < 0) {
            return IO_ERROR;
        }
    }

    return OK;
}
