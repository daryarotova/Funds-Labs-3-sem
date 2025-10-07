#ifndef CONVERSE_H
#define CONVERSE_H

#include <stdlib.h>

long long strToInt(const char* str, int base);
void intToStr(long long value, int base, char* result);
void reverseStr(char* str, int length);

#endif
