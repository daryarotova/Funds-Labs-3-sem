#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/checking.h"
#include "include/outputing.h"
#include "include/solving.h"
#include "include/errors.h"

enum {
    SUCCESS = 0,
    ERROR_WITHOUT_PARAMETERS,
    ERROR_INVALID_PARAMETER,
    ERROR_INVALID_ARGUMENT,
    ERROR_UNKNOWN_FLAG
};

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printTableWithInstructions();
        return ERROR_WITHOUT_PARAMETERS;
    }

    const char *flag = argv[1];

    if (strcmp(flag, "-q") == 0 || strcmp(flag, "/q") == 0) {
        if (argc != 6) {
            printTableWithInstructions();
            return ERROR_INVALID_PARAMETER;
        }

        errorCodes errE = isRightDoubleNum(argv[2]);
        errorCodes errA = isRightDoubleNum(argv[3]);
        errorCodes errB = isRightDoubleNum(argv[4]);
        errorCodes errC = isRightDoubleNum(argv[5]);

        if (errE != OK || errA != OK || errB != OK || errC != OK) {
            printTableWithInstructions();
            return ERROR_INVALID_ARGUMENT;
        }

        double epsilon = strtod(argv[2], NULL); // strtod - строку в число двойной точности (double)
        double a = strtod(argv[3], NULL);
        double b = strtod(argv[4], NULL);
        double c = strtod(argv[5], NULL);

        double roots[2];
        errorCodes solveErr = solveQuadraticEquation(epsilon, a, b, c, roots);
        if (solveErr == NO_RESULT || solveErr == OVERFLOW) {
            printQuadraticSolution(roots, 6, a, b, c);
        } else {
            int precision = 1;
            double epsCopy = epsilon;
            while (epsCopy < 1.0) {
                ++precision;
                epsCopy *= 10.0;
            }
            printQuadraticSolution(roots, precision, a, b, c);
        }
    }
    else if (strcmp(flag, "-m") == 0 || strcmp(flag, "/m") == 0) {
        if (argc != 4) {
            printTableWithInstructions();
            return ERROR_INVALID_PARAMETER;
        }

        errorCodes errX = isRightIntNum(argv[2]);
        errorCodes errY = isRightIntNum(argv[3]);

        if (errX != OK || errY != OK) {
            printTableWithInstructions();
            return ERROR_INVALID_ARGUMENT;
        }

        int x = atoi(argv[2]); // atoi - строку в целое число
        int y = atoi(argv[3]);

        if (x == 0 || y == 0) {
            printf("Ошибка: нужно вводить ненулевые значения\n\n");
            printTableWithInstructions();
            return ERROR_INVALID_ARGUMENT;
        }

        if (x % y == 0) {
            printf("%d делится на %d\n", x, y);
        } else {
            printf("%d не делится на %d\n", x, y);
        }
    }
    else if (strcmp(flag, "-t") == 0 || strcmp(flag, "/t") == 0) {
        if (argc != 6) {
            printTableWithInstructions();
            return ERROR_INVALID_PARAMETER;
        }

        errorCodes errE = isRightDoubleNum(argv[2]);
        errorCodes errA = isRightDoubleNum(argv[3]);
        errorCodes errB = isRightDoubleNum(argv[4]);
        errorCodes errC = isRightDoubleNum(argv[5]);

        if (errE != OK || errA != OK || errB != OK || errC != OK) {
            printTableWithInstructions();
            return ERROR_INVALID_ARGUMENT;
        }

        double epsilon = strtod(argv[2], NULL);
        double sideA = strtod(argv[3], NULL);
        double sideB = strtod(argv[4], NULL);
        double sideC = strtod(argv[5], NULL);

        int isRight = 0;
        errorCodes triErr = isRightTriangle(epsilon, sideA, sideB, sideC, &isRight);
        if (triErr != OK) {
            printf("Ошибка вычисления треугольника\n");
            return ERROR_INVALID_ARGUMENT;
        }

        if (isRight) {
            printf("Это прямоугольный треугольник.\n");
        } else {
            printf("Это не прямоугольный треугольник.\n");
        }
    }
    else {
        printTableWithInstructions();
        return ERROR_UNKNOWN_FLAG;
    }

    return SUCCESS;
}
