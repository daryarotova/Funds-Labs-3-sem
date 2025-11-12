#include "../include/convert.h"

unsigned int addBits(unsigned int a, unsigned int b) {
    while (b != 0) {
        unsigned int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

unsigned int subBits(unsigned int a, unsigned int b) {
    while (b != 0) {
        unsigned int borrow = (~a) & b;
        a = a ^ b;
        b = borrow << 1;
    }
    return a;
}

StatusCode convertNumber(unsigned int num, const int r, char *out, unsigned int out_size) {
    if (r < 1 || r > 5) {
        return ERROR_WRONG_R;
    }
    
    if (out == 0) {
        return ERROR_INVALID_ARG;
    }

    if (out_size < 2) {
        return ERROR_MALLOC;
    }

    char temp[65];
    const char symbols[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int mask = subBits(1 << r, 1);
    unsigned int index = 0;

    if (num == 0) {
        out[0] = '0';
        out[1] = '\0';
        return OK;
    }

    while (num > 0 && index < 64) {
        unsigned int part = num & mask;
        temp[index] = symbols[part];
        index = addBits(index, 1);
        num >>= r;
    }

    if (addBits(index, 1) > out_size) {
        return ERROR_MALLOC;
    }

    unsigned int k = 0;
    while (index > 0) {
        index = subBits(index, 1);
        out[k] = temp[index];
        k = addBits(k, 1);
    }

    out[k] = '\0';
    return OK;
}
