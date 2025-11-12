#include "include/convert.h"
#include <stdio.h>

int main() {
    StatusCode status;
    char result[50];

    status = convertNumber(0, 1, result, 50);
    printf("Test 1: n = 0, r = 1\n");
    if (status == OK) {
        printf("Result: %s\n", result);
    } else {
        printf("Failed: code %d\n", status);
    }
    
    status = convertNumber(7, 1, result, 50);
    printf("Test 2: n = 7, r = 1\n");
    if (status == OK) {
        printf("Result: %s\n", result);
    } else {
        printf("Failed: code %d\n", status);
    }

    status = convertNumber(10, 2, result, 50);
    printf("Test 3: n = 10, r = 2\n");
    if (status == OK) {
        printf("Result: %s\n", result);
    } else {
        printf("Failed: code %d\n", status);
    }

    status = convertNumber(17, 3, result, 50);
    printf("Test 4: n = 17, r = 3\n");
    if (status == OK) {
        printf("Result: %s\n", result);
    } else {
        printf("Failed: code %d\n", status);
    }

    status = convertNumber(24, 4, result, 50);
    printf("Test 5: n = 24, r = 4\n");
    if (status == OK) {
        printf("Result: %s\n", result);
    } else {
        printf("Failed: code %d\n", status);
    }

    status = convertNumber(43, 5, result, 50);
    printf("Test 6: n = 43, r = 5\n");
    if (status == OK) {
        printf("Result: %s\n", result);
    } else {
        printf("Failed: code %d\n", status);
    }

    status = convertNumber(31, 5, result, 50);
    printf("Test 7: n = 31, r = 5\n");
    if (status == OK) {
        printf("Result: %s\n", result);
    } else {
        printf("Failed: code %d\n", status);
    }

    return 0;
}
