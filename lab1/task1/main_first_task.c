#include "functions.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Проверка количества аргументов
    if (argc != 3) {
        printf("Некорректное количество аргументов\n");
        return (int)INVALID_ARGUMENT;
    }

    // Парсинг числа
    int x = 0;
    errorCodes status = parsing((const char *)argv[1], &x);
    if (status != OK) {
        if (status == INVALID_ARGUMENT) {
            printf("Некорректный ввод\n");
        } else if (status == OUT_RANGE) {
            printf("Число выходит за пределы допустимого диапазона\n");
        } else {
            printf("Ошибка преобразования числа\n");
        }
        return (int)status;
    }

    // Проверка флага: первый символ '-' или '/', ровно один символ-флаг после него
    const char *flag = (const char *)argv[2];
    if (flag == NULL || (flag[0] != '-' && flag[0] != '/') || flag[1] == '\0' || flag[2] != '\0') {
        printf("Некорректный флаг\n");
        return (int)INVALID_ARGUMENT;
    }

    // буква флага: например 'h' из "-h" или "/h"
    char f = flag[1];

    errorCodes result = UNKNOWN_FLAG;

    if (f == 'h') {
        result = printNaturalNum(x);
        if (result == NO_RESULT) {
            printf("Нет натуральных чисел, меньших или равных 100, кратных %d.\n", x);
        } else if (result == INVALID_ARGUMENT) {
            printf("Нельзя делить на 0.\n");
        }
    } else if (f == 'p') {
        result = simpleOrNot(x);
    } else if (f == 's') {
        result = splitIntoHex(x);
    } else if (f == 'e') {
        unsigned long long table[10][10];
        size_t rows = 0, cols = 0;
        result = makeTableOfPowers(x, table, &rows, &cols);
        if (result == OK) {
            printf("Таблица степеней (основания 1-10, степени 1-%d):\n", x);
            for (size_t i = 0; i < rows; i++) {
                printf("%2zu:", i + 1);
                for (size_t j = 0; j < cols; j++) {
                    printf(" %llu", table[i][j]);
                }
                printf("\n");
            }
        } else if (result == OUT_RANGE) {
            printf("Ошибка: для флага -e число x должно быть в диапазоне от 1 до 10 включительно.\n");
        }
    } else if (f == 'a') {
        result = summaNaturalNum(x);
        if (result == INVALID_ARGUMENT) {
            printf("Некорректный ввод\n");
        }
    } else if (f == 'f') {
        result = factorialOfX(x);
        if (result == INVALID_ARGUMENT) {
            printf("Некорректный ввод\n");
        }
    } else {
        printf("Неизвестный флаг\n");
        return (int)UNKNOWN_FLAG;
    }

    if (result != OK) {
        if (result == OVERFLOW) {
            printf("Произошло переполнение\n");
        } else if (result == IO_ERROR) {
            printf("Ошибка ввода/вывода\n");
        }
    }

    return (int)result;
}
