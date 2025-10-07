#include "../include/converse.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseStr(char* str, int length) {
    if (!str) {
        return;
    }

    int i = 0;
    int j = length - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

long long strToInt(const char* str, int base) {
    if (!str) {
        return 0;
    }

    long long result = 0;
    int sign = 1;
    int startPosition = 0;

    if (str[0] == '-') {
        sign = -1;
        startPosition = 1;
    } else if (str[0] == '+') {
        startPosition = 1;
    }

    for (int i = startPosition; str[i] != '\0'; i++) {
        char currentChar = str[i];
        int digit = 0;

        if (currentChar >= '0' && currentChar <= '9') {
            digit = currentChar - '0';
        } else if (currentChar >= 'A' && currentChar <= 'Z') {
            digit = 10 + (currentChar - 'A');
        } else if (currentChar >= 'a' && currentChar <= 'z') {
            digit = 10 + (currentChar - 'a');
        } else {
            break;
        }
        result = result * base + digit;
    }

    return sign * result;
}


void intToStr(long long value, int base, char* result) {
    if (!result) {
        return;
    }

    int sign = 0;
    if (value < 0) {
        sign = 1;
        value = -value;
    }

    int index = 0;

    if (value == 0) {
        result[index++] = '0';
    }

    while (value > 0) {
        int digit = value % base;
        if (digit < 10) {
            result[index++] = '0' + digit;
        } else {
            result[index++] = 'A' + (digit - 10);
        }
        value /= base;
    }

    if (sign) {
        result[index++] = '-';
    }

    reverseStr(result, index);
    result[index] = '\0';
}
