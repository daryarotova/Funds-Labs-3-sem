#include "../include/checking.h"
#include <string.h> // strlen

errorCodes isRightDoubleNum(const char *str) {
    if (str == 0 || *str == '\0') {
        return INVALID_ARGUMENT;
    }

    const char *ptr = str;

    if (*ptr == '-' || *ptr == '+') { // проверка знака
        ptr++;
        if (*ptr == '\0') {
            return INVALID_ARGUMENT;
        }
    }

    int hasDot = 0; // точка
    int hasDigit = 0; // значение

    while (*ptr != '\0') {
        if (*ptr == '.') {
            if (hasDot) {
                return INVALID_ARGUMENT; // две точки
            }
            hasDot = 1;
        } else if (*ptr >= '0' && *ptr <= '9') {
            hasDigit = 1;
        } else {
            return INVALID_ARGUMENT; // посторонний символ
        }
        ptr++;
    }

    if (!hasDigit) {
        return INVALID_ARGUMENT; // нет цифр
    }

    if (*(ptr - 1) == '.') {
        return INVALID_ARGUMENT; // точка - последний символ
    }

    if (strlen(str) > 50) {
        return OUT_RANGE;
    }

    return OK;
}

errorCodes isRightIntNum(const char *str) {
    if (str == 0 || *str == '\0') {
        return INVALID_ARGUMENT;
    }

    const char *ptr = str;

    if (*ptr == '-' || *ptr == '+') {
        ptr++;
        if (*ptr == '\0') {
            return INVALID_ARGUMENT;
        }
    }

    int length = 0;
    while (*ptr != '\0') {
        if (!(*ptr >= '0' && *ptr <= '9')) {
            return INVALID_ARGUMENT;
        }
        length++;
        ptr++;
    }

    if (length == 0) {
        return INVALID_ARGUMENT;
    }

    if (length > 10) { // для int максимум 10 символов (2147483647)
        return OUT_RANGE;
    }

    return OK;
}
