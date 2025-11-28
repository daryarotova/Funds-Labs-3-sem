#include "../include/utils.h"
#include <string.h>
#include <ctype.h>

void normalize_string(char* s) {
    if (!s) return;
    
    char* dst = s;
    char* src = s;
    
    while (*src && isspace(*src)) src++;
    
    while (*src) {
        if (!isspace(*src)) {
            *dst++ = *src;
        }
        src++;
    }
    
    *dst = '\0';
}

void detect_command(const char* s, CommandType* cmd) {
    if (!s || !cmd) return;
    
    char lower[256];
    strncpy(lower, s, sizeof(lower) - 1);
    lower[sizeof(lower) - 1] = '\0';
    for (char* p = lower; *p; p++) {
        *p = tolower(*p);
    }
    
    if (strstr(lower, "print(") == lower) {
        *cmd = CMD_PRINT;
    } else if (strchr(lower, '=') != NULL) {
        *cmd = CMD_SET;
    } else {
        *cmd = CMD_INVALID;
    }
}

int int_power(int base, int exp) {
    if (exp < 0) return 0;
    if (exp == 0) return 1;
    
    int result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return result;
}

bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '=';
}