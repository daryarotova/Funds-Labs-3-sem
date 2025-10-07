#include "../include/validate.h"
#include <ctype.h>
#include <string.h>

int validateBase(const char* str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }

    int base = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
        
        base = base * 10 + (str[i] - '0');
    }

    if (base < 2 || base > 36) {
        return 0;
    }
    
    return base;
}

int validateNumber(const char* number, int base) {
    if (number == NULL || number[0] == '\0') {
        return 0;
    }

    int start = 0;
    if (number[0] == '+' || number[0] == '-') {
        start = 1;
    }

    for (int i = start; number[i] != '\0'; i++) {
        char c = number[i];
        int value = -1;

        if (isdigit(c)) {
            value = c - '0';
        }
        else if (c >= 'A' && c <= 'Z') {
            value = 10 + (c - 'A');
        }
        else if (c >= 'a' && c <= 'z') {
            value = 10 + (c - 'a');
        }

        if (value < 0 || value >= base) {
            return 0;
        }
    }

    return 1;
}
