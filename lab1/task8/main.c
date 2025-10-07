#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/validate.h"
#include "include/converse.h"

enum {
    OK = 0,
    WRONG_BASE = 1,
    WRONG_NUMBER = 2
};

void toUpperCase(char* str) {
    if (!str) {
        return;
    }

    for (int i = 0; str[i] != '\0'; ++i) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

int main(void) {
    const int MAX_INPUT_LENGTH = 256;
    char inputBuffer[MAX_INPUT_LENGTH];
    int base = 0;

    printf("Введите основание системы счисления [2, 36]: ");
    if (!fgets(inputBuffer, MAX_INPUT_LENGTH, stdin)) {
        printf("Ошибка при вводе основания\n");
        return WRONG_BASE;
    }
    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

    if (!validateBase(inputBuffer)) {
        printf("Введите основание системы счисления от 2 до 36\n");
        return WRONG_BASE;
    }

    base = atoi(inputBuffer);
    if (base < 2 || base > 36) {
        printf("Введите основание системы счисления от 2 до 36\n");
        return WRONG_BASE;
    }

    long long maxValue = 0;
    int isFirstNumber = 1;

    printf("Введите числа (для окончания введите Stop):\n");

    while (1) {
        if (!fgets(inputBuffer, MAX_INPUT_LENGTH, stdin)) {
            printf("Ошибка при вводе числа\n");
            return WRONG_NUMBER;
        }

        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        char tempBuffer[MAX_INPUT_LENGTH];
        strncpy(tempBuffer, inputBuffer, MAX_INPUT_LENGTH);
        
        tempBuffer[MAX_INPUT_LENGTH - 1] = '\0';
        toUpperCase(tempBuffer);

        if (strcmp(tempBuffer, "STOP") == 0) {
            break;
        }

        if (!validateNumber(inputBuffer, base)) {
            printf("Недопустимое число для данного основания\n");
            continue;
        }

        long long currentValue = strToInt(inputBuffer, base);
        if (isFirstNumber || llabs(currentValue) > llabs(maxValue)) {
            maxValue = currentValue;
            isFirstNumber = 0;
        }
    }

    if (isFirstNumber) { 
        printf("Числа не были введены\n");
        return OK;
    }

    char resultBuffer[MAX_INPUT_LENGTH];

    printf("\nМаксимальное по модулю число: %lld\n", maxValue);

    intToStr(maxValue, 9, resultBuffer);
    printf("В системе с основанием 9: %s\n", resultBuffer);

    intToStr(maxValue, 18, resultBuffer);
    printf("В системе с основанием 18: %s\n", resultBuffer);

    intToStr(maxValue, 27, resultBuffer);
    printf("В системе с основанием 27: %s\n", resultBuffer);

    intToStr(maxValue, 36, resultBuffer);
    printf("В системе с основанием 36: %s\n", resultBuffer);

    return OK;
}
