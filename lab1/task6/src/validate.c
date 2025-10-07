#include "../include/validate.h"
#include <string.h>

int isDoubleString(char* input) {
    int index = 0;

    if (input == NULL || input[index] == '\0') {
        return 0;
    }

    if (input[index] == '.') {
        return 0;
    }

    int length = strlen(input);

    if (input[index] == '0') {
        if (length > 1) {
            if (input[index + 1] != '.') {
                return 0;
            }
        }
    }

    if (input[index] == '-') {
        return 0;
    }

    if (input[index] == '+') {
        return 0;
    }

    int commaFlag = 0;
    for (int i = index; i < length; i++) {
        if (input[i] == '.' && commaFlag) {
            return 0;
        } else if (input[i] == '.') {
            commaFlag = 1;
            continue;
        } else if (input[i] >= '0' && input[i] <= '9') {
            continue;
        }
        return 0;
    }

    if (input[length - 1] == '.') {
        return 0;
    }

    return 1;
}