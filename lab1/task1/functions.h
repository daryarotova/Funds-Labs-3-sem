#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    OK = 0,
    INVALID_ARGUMENT = 1,
    OUT_RANGE = 2, // выход за допустимый диапазон
    NO_RESULT = 3, // не может быть посчитан рез-т
    OVERFLOW = 4, 
    IO_ERROR = 5, // ошибка input / output
    UNKNOWN_FLAG = 6 // неизвестный флаг
} errorCodes;

errorCodes parsing(const char *in_str, int *out_value); // парсинг целого числа из строки
errorCodes printNaturalNum(const int x); // a - вывод натуральных чисел <=100, которые кратны x
errorCodes simpleOrNot(const int x); // b - проверка простоты/составности числа x
errorCodes splitIntoHex(const int x); // c - разделение на hex-цифры и вывод от старших к младшим
errorCodes makeTableOfPowers(const int x, unsigned long long table[10][10], size_t *rows, size_t *cols); // d - построение таблицы степеней (основания 1-10, показатели 1-x)
errorCodes summaNaturalNum(const int x); // e - сумма натуральных чисел от 1 до x
errorCodes factorialOfX(const int x); // f - факториал числа

#endif // FUNCTIONS_H
