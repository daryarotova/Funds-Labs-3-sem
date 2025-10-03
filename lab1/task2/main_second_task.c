#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/primes.h"

int main() {
    const unsigned long long MAX_NUMBER = 1000000ULL; // максимум для номера числа
    char buffer[100]; // буфер для ввода
    unsigned long long t; // количество запросов

    printf("Введите количество запросов: ");

    if (scanf("%99s", buffer) != 1) {
        printf("Ошибка ввода количества запросов.\n");
        return 1;
    }

    if (buffer[0] == '-') {
        printf("Количество запросов должно быть положительным\n");
        return 1;
    }

    char *endptr;
    t = strtoull(buffer, &endptr, 10);

    if (*endptr != '\0') {
        printf("Некорректный ввод числа запросов\n");
        return 1;
    }

    if (t == 0) {
        printf("Количество запросов должно быть положительным\n");
        return 1;
    }

    if (t > MAX_NUMBER) {
        printf("Количество запросов слишком большое (максимум %llu)\n", MAX_NUMBER);
        return 1;
    }

    int *inputNumbers = (int *)malloc(sizeof(int) * t); // массив входных данных
    if (inputNumbers == NULL) {
        printf("Ошибка выделения памяти для массива входных данных\n");
        return 1;
    }

    printf("Введите %llu порядковых номеров простых чисел:\n", t);

    for (unsigned long long i = 0; i < t; ++i) {
        if (scanf("%99s", buffer) != 1) {
            printf("Ошибка ввода числа\n");
            free(inputNumbers);
            return 1;
        }

        inputNumbers[i] = (int)strtol(buffer, &endptr, 10);

        if (*endptr != '\0') {
            printf("Некорректный ввод числа\n");
            free(inputNumbers);
            return 1;
        }

        if (inputNumbers[i] <= 0) {
            printf("Номер простого числа должен быть положительным\n");
            free(inputNumbers);
            return 1;
        }

        if ((unsigned long long)inputNumbers[i] > MAX_NUMBER) {
            printf("Номер простого числа должен быть до максимума %llu\n", MAX_NUMBER);
            free(inputNumbers);
            return 1;
        }
    }

    for (unsigned long long i = 0; i < t; ++i) {
        int prime = 0;
        errorCodes status = nThPrime((size_t)inputNumbers[i], &prime);

        if (status != OK) {
            printf("Ошибка при вычислении %d-го простого числа\n", inputNumbers[i]);
        } else {
            printf("Простое число под номером %d это: %d\n", inputNumbers[i], prime);
        }
    }

    free(inputNumbers);
    return 0;
}
