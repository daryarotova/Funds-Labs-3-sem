#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "include/functions.h"
#include "include/validate.h"

enum {
    OK = 0,
    INVALID_ARGUMENT = 1,
    INVALID_EPSILON = 2,
    FAILED_COMPUTATION = 3
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Неверное количество аргументов\n");
        printf("Использование: ./main.out <эпсилон> \n");
        return INVALID_ARGUMENT;
    }

    double flag = isDoubleString(argv[1]);
    if (flag == 0) {
        printf("Введите вещественное число эпсилон больше нуля\n");
        return INVALID_EPSILON;
    }

    double epsilon = atof(argv[1]);
    if (epsilon <= 0.0) {
        printf("Эпсилон должен быть положительным числом\n");
        return INVALID_EPSILON;
    }

    const double a = 0.0;
    const double b = 1.0;

    double resultA = calculateIntegral(functionA, epsilon, a, b);
    double resultB = calculateIntegral(functionB, epsilon, a, b);
    double resultC = calculateIntegral(functionC, epsilon, a, 1.0 - epsilon);
    double resultD = calculateIntegral(functionD, epsilon, a, b);

    if (isnan(resultA) || isnan(resultB) || isnan(resultC) || isnan(resultD)) {
        printf("Ошибка при вычислении интегралов\n");
        return FAILED_COMPUTATION;
    }

    printf("Первый интеграл: ln(1+x)/x dx = %.15f\n", resultA);
    printf("Второй интеграл: e^(-x^2 / 2) dx = %.15f\n", resultB);
    printf("Третий интеграл: ln(1/(1-x)) dx = %.15f\n", resultC);
    printf("Четвертый интеграл: x^x dx = %.15f\n", resultD);

    return OK;
}