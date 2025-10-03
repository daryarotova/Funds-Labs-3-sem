#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>


/* parsing:
   безопасный разбор строки в int, проверяет:
   - NULL-параметры;
   - корректность символов;
   - один знак + или - допустим;
   - не допускает lone-sign ("+" или "-");
   - проверка выхода за диапазон int.
*/

errorCodes parsing(const char *in_str, int *out_value) { // no dinamic memory
    if (in_str == NULL || out_value == NULL) { // wrong input or output
        return INVALID_ARGUMENT;
    }

    const char *p = in_str;
    int sign = 1;
    if (*p == '+' || *p == '-') {
        if (*p == '-') {
            sign = -1;
        }
        p++;
        if (*p == '\0') { // if only a sign
            return INVALID_ARGUMENT;
        }
    }

    long long acc = 0LL; 
    while (*p != '\0') {
        char ch = *p;
        if (ch < '0' || ch > '9') {
            return INVALID_ARGUMENT;
        }
        int digit = ch - '0';
        acc = acc * 10LL + (long long)digit;
        if (sign > 0) {
            if (acc > (long long)INT_MAX) {
                return OUT_RANGE;
            }
        } else {
            if (-acc < (long long)INT_MIN) {
                return OUT_RANGE;
            }
        }
        p++;
    }

    if (sign > 0) {
        *out_value = (int)acc;
    } else {
        *out_value = (int)(-acc);
    }

    return OK;
}

/* a) printNaturalNum:
   печатает натуральные числа 1-100, кратные |x|.
   x == 0 => INVALID_ARGUMENT (деление на 0)
   возвращает NO_RESULT если не найдено ни одного числа
*/

errorCodes printNaturalNum(const int x) {
    if (x == 0) {
        return INVALID_ARGUMENT;
    }

    int absX = x;
    if (absX < 0) {
        absX = -absX;
    }

    int foundNum = 0;
    int results[100]; // local massive - stek's memory, without dinamic
    int resultNum = 0;

    for (int i = 1; i <= 100; i++) {
        if ((i % absX) == 0) {
            if (resultNum < 100) {
                results[resultNum] = i;
                resultNum++;
                foundNum = 1;
            } else {
                return IO_ERROR; // if overflow
            }
        }
    }

    if (!foundNum) {
        return NO_RESULT;
    }

    for (int i = 0; i < resultNum; i++) {
        printf("%d", results[i]);
        if (i + 1 < resultNum) {
            printf(" ");
        }
    }

    printf("\n");
    return OK;
}

/* b) simpleOrNot:
   определяет простое / составное; для x <= 1 возвращает NO_RESULT и сообщение.
   используем проверку делителей до целочисленного sqrt(x).
*/

errorCodes simpleOrNot(const int x) {
    if (x <= 1) {
        printf("Число %d не входит в группу простых или составных чисел.\n", x);
        return NO_RESULT;
    }

    if (x == 2) {
        printf("Число 2 ялвяется простым числом.\n");
        return OK;
    }

    if ((x % 2) == 0) {
        printf("Число %d составное.\n", x);
        return OK;
    }

    // local variables
    int limit = (int)sqrt((double)x); // checking divisors up to sqrt(x)
    for (int i = 3; i <= limit; i += 2) {
        if ((x % i) == 0) {
            printf("Число %d составное.\n", x);
            return OK;
        }
    }

    printf("Число %d является простым.\n", x);
    return OK;
}

/* c) splitIntoHex:
   печатает шестнадцатеричные цифры от старших к младшим, разделяя пробелом,
   без ведущих нулей. Отрицательные числа — печатаем знак '-' отдельно.
*/

errorCodes splitIntoHex(const int x) {
    unsigned int number;

    if (x < 0) {
        long long neg = -(long long)x;
        if (neg > (long long)UINT_MAX) {
            return OUT_RANGE;
        }
        number = (unsigned int)neg;
    } else {
        number = (unsigned int)x;
    }

    if (number == 0) {
        printf("0\n");
        return OK;
    }

    char buffer[32]; // local massive
    int amountOfNum = snprintf(buffer, sizeof(buffer), "%X", number); // %X - вывод числа в 16 сс, pointer to a string
    if (amountOfNum < 0 || amountOfNum >= (int)sizeof(buffer)) {
        return IO_ERROR;
    }

    size_t len = strlen(buffer); // pointer to a string

    if (x < 0) {
        printf("- ");
    }

    for (size_t i = 0; i < len; i++) {
        printf("%c", buffer[i]);
        if (i + 1 < len) {
            printf(" ");
        }
    }

    printf("\n");
    return OK;
}

/* d) makeTableOfPowers:
   таблица base=1..10, exp=1..x; ограничение 1<=x<=10.
   функция только формирует таблицу.
   проверка переполнения перед умножением.
*/

errorCodes makeTableOfPowers(const int x, unsigned long long table[10][10], size_t *rows, size_t *cols) {
    if (x < 1 || x > 10) {
        return OUT_RANGE;
    }

    if (table == NULL || rows == NULL || cols == NULL) {
        return INVALID_ARGUMENT;
    }

    *rows = 10;
    *cols = (size_t)x;

    for (size_t base = 1; base <= 10; base++) {
        unsigned long long value = 1ULL;
        for (size_t exp = 1; exp <= (size_t)x; exp++) {
            if (value > ULLONG_MAX / base) { // overflow check before multiplication
                return OVERFLOW;
            }
            value *= base;
            table[base - 1][exp - 1] = value;
        }
    }

    return OK;
}

/* e) summaNaturalNum:
   сумма 1..x, x >= 1; проверка переполнения в long long.
*/

errorCodes summaNaturalNum(const int x) {
    if (x < 1) { // only natural
        return INVALID_ARGUMENT;
    }

    long long number = (long long)x;
    long long summa = (number * (number + 1)) / 2; // x * (x + 1) / 2
    printf("%lld\n", summa);
    return OK;
}

/* f) factorialOfX:
   факториал в unsigned long long, x >= 0.
*/

errorCodes factorialOfX(const int x) {
    if (x < 0) {
        return INVALID_ARGUMENT;
    }

    unsigned long long result = 1ULL;

    for (int i = 1; i <= x; i++) {
        unsigned long long newI = (unsigned long long)i;
        if (result > ULLONG_MAX / newI) { // overflow check before multiplication
            return OVERFLOW;
        }
        result *= newI;
    }
    printf("%llu\n", result);
    return OK;
}