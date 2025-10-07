#include "../include/solve.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static int charToDigit(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }

    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }

    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    }

    return -1;
}

errorCodes analyzeNumber(const char* number, int* outBase, uint64_t* outValue) {
    if (number == NULL || outBase == NULL || outValue == NULL) {
        return INVALID_ARGUMENT;
    }

    size_t length = strlen(number);
    if (length == 0) {
        return PARSE_ERROR;
    }

    int maxDigit = -1;
    for (size_t i = 0; i < length; ++i) {
        if (isspace((unsigned char)number[i])) {
            return PARSE_ERROR;
        }
        int digit = charToDigit(number[i]);
        if (digit == -1) {
            return PARSE_ERROR;
        }
        if (digit > maxDigit) {
            maxDigit = digit;
        }
    }
    
    int base = 0;
    if (maxDigit < 1) {
        base = 2;
    } else {
        base = maxDigit + 1;
    }

    if (base < 2 || base > 36) {
        return PARSE_ERROR;
    }

    uint64_t value = 0;
    for (size_t i = 0; i < length; ++i) {
        int digit = charToDigit(number[i]);
        if (digit >= base) {
            return PARSE_ERROR;
        }
        if (value > (UINT64_MAX - (uint64_t)digit) / (uint64_t)base) {
            return OVERFLOW;
        }
        value = value * (uint64_t)base + (uint64_t)digit;
    }

    *outBase = base;
    *outValue = value;

    return OK;
}

static const char* skipLeadingZeros(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    const char* p = str;
    while (*p == '0') {
        ++p;
    }

    if (*p == '\0') { // consisted only of zeros
        return p - 1;
    }

    return p;
}

errorCodes solve(FILE * input, FILE * output) {
    if (input == NULL || output == NULL) {
        return INVALID_ARGUMENT;
    }

    char buffer[256];
    while (fscanf(input, "%255s", buffer) == 1) {
        const char* standart = skipLeadingZeros(buffer);

        int base = 0;
        uint64_t value = 0;
        errorCodes status = analyzeNumber(standart, &base, &value);
        
        if (status != OK) {
            return status;
        }

        fprintf(output, "%s %d %llu\n", standart, base, (unsigned long long)value);
    }

    if (ferror(input) != 0 || ferror(output) != 0) {
        return IO_ERROR;
    }

    return OK;
}