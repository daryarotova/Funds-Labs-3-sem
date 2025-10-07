#include "../include/flags.h"
#include "../include/conversion.h"
#include <stdio.h>

void dFlag(FILE* fileInput, FILE* fileOutput) {
    int c;
    while ((c = fgetc(fileInput)) != EOF) {
        if (!(c >= '0' && c <= '9')) {
            fputc(c, fileOutput);
        }
    }
}

void iFlag(FILE* fileInput, FILE* fileOutput) {
    int count = 0;
    int c;
    while ((c = fgetc(fileInput)) != EOF) {
        if (c == '\n') {
            fprintf(fileOutput, "%d\n", count);
            count = 0;
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            count++;
        }
    }
    if (count > 0) {
        fprintf(fileOutput, "%d\n", count);
    }
}

void sFlag(FILE* fileInput, FILE* fileOutput) {
    int count = 0;
    int c;
    while ((c = fgetc(fileInput)) != EOF) {
        if (c == '\n') {
            fprintf(fileOutput, "%d\n", count);
            count = 0;
        } else if (!((c >= 'a' && c <= 'z') || 
                    (c >= 'A' && c <= 'Z') || 
                    (c >= '0' && c <= '9') || 
                    c == ' ')) {
            count++;
        }
    }
    if (count > 0) {
        fprintf(fileOutput, "%d\n", count);
    }
}

void aFlag(FILE* fileInput, FILE* fileOutput) {
    int c;
    char hexBuffer[34];
    while ((c = fgetc(fileInput)) != EOF) {
        if (c >= '0' && c <= '9') {
            fputc(c, fileOutput);
        } else {
            int startPosition = tenToHex(hexBuffer, c);
            if (startPosition >= 0) {
                for (int i = startPosition; i < 33 && hexBuffer[i] != '\0'; i++) {
                    fputc(hexBuffer[i], fileOutput);
                }
            }
        }
    }
}
