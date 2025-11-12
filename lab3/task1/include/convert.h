#ifndef CONVERT_H
#define CONVERT_H

typedef enum {
    OK = 0,
    ERROR_MALLOC,
    ERROR_INVALID_ARG,
    ERROR_WRONG_R
} StatusCode;

unsigned int addBits(unsigned int a, unsigned int b);
unsigned int subBits(unsigned int a, unsigned int b);

StatusCode convertNumber(const unsigned int num, const int r, char *out, unsigned int out_size);

#endif
