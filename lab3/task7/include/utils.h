#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    CMD_SET,
    CMD_PRINT,
    CMD_INVALID
} CommandType;

void normalize_string(char* s);
void detect_command(const char* s, CommandType* cmd);
int int_power(int base, int exp);
bool is_operator(char c);

#endif
