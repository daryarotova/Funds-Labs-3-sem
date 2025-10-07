#include "../include/conversion.h"
#include <stdio.h>

int tenToHex(char* result, int number) {
    if (result == NULL) {
        return -1;
    }

    int index = 32;
    int digit = 0;

    if (number == 0) {
        result[0] = '0';
        result[1] = '\0';
        return 0;
    }

    while (number != 0) {
        digit = number % 16;
        if (digit <= 9) {
            result[index] = '0' + digit;
        } else {
            result[index] = 'A' + (digit - 10);
        }
        number /= 16;
        index--;
    }
    return ++index;
}
