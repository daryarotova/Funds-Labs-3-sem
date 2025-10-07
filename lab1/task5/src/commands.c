#include "../include/commands.h"
#include "../include/flags.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

errorCodes parseCommandLine(int argc, char* argv[], commandLineArgs* args) { // parsing args from command line and filling in the structure
    if (args == NULL) {
        return INVALID_ARGUMENT;
    }

    if (argc < 2) {
        return INVALID_ARGUMENT;
    }

    strncpy(args->flag, argv[1], sizeof(args->flag) - 1);
    args->flag[sizeof(args->flag) - 1] = '\0';

    if (args->flag[1] == 'n') {
        if (argc != 4) {
            return INVALID_ARGUMENT;
        }
        strncpy(args->inputFilePath, argv[2], sizeof(args->inputFilePath) - 1);
        strncpy(args->outputFilePath, argv[3], sizeof(args->outputFilePath) - 1);
        args->hasFileOutput = 1;
    } else {
        if (argc != 3) {
            return INVALID_ARGUMENT;
        }
        strncpy(args->inputFilePath, argv[2], sizeof(args->inputFilePath) - 1);
        
        const char* prefix = "out_";
        const char* inputName = args->inputFilePath;
        const char* lastSlash = strrchr(inputName, '/');
        
        if (lastSlash != NULL) {
            inputName = lastSlash + 1;
        }
        
        strcpy(args->outputFilePath, prefix);
        strncat(args->outputFilePath, inputName, sizeof(args->outputFilePath) - strlen(prefix) - 1);
        args->hasFileOutput = 0;
    }

    args->inputFilePath[sizeof(args->inputFilePath) - 1] = '\0';
    args->outputFilePath[sizeof(args->outputFilePath) - 1] = '\0';

    return OK;
}

errorCodes validateFile(const char* path) {
    if (path == NULL || path[0] == '\0') {
        return INVALID_ARGUMENT;
    }

    if (strlen(path) >= 256) {
        return OUT_OF_RANGE;
    }

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        return IO_ERROR;
    }
    fclose(file);

    return OK;
}

errorCodes validateFlag(const char* flag) {
    if (flag == NULL || flag[0] == '\0') {
        return INVALID_ARGUMENT;
    }

    if (flag[0] != '-' && flag[0] != '/') { // first symbol
        return INVALID_FLAG_FORMAT;
    }

    if (flag[1] == 'n') { // with n
        if (strlen(flag) != 3) {
            return INVALID_FLAG_FORMAT;
        }
        char actualFlag = flag[2];
        if (actualFlag != 'd' && actualFlag != 'i' && actualFlag != 's' && actualFlag != 'a') {
            return UNKNOWN_FLAG;
        }
    } 
    else { // without n
        if (strlen(flag) != 2) {
            return INVALID_FLAG_FORMAT;
        }
        char actualFlag = flag[1];
        if (actualFlag != 'd' && actualFlag != 'i' && actualFlag != 's' && actualFlag != 'a') {
            return UNKNOWN_FLAG;
        }
    }

    return OK;
}

errorCodes processFile(const commandLineArgs* args) { // launching functions with flags
    if (args == NULL) {
        return INVALID_ARGUMENT;
    }

    FILE* inputFile = fopen(args->inputFilePath, "r");
    if (inputFile == NULL) {
        return IO_ERROR;
    }

    FILE* outputFile = fopen(args->outputFilePath, "w");
    if (outputFile == NULL) {
        fclose(inputFile);
        return IO_ERROR;
    }

    char actualFlag; // our flag now
    if (args->flag[1] == 'n') {
        actualFlag = args->flag[2];
    } else {
        actualFlag = args->flag[1];
    }

    switch (actualFlag) {
        case 'd':
            dFlag(inputFile, outputFile);
            break;
        case 'i':
            iFlag(inputFile, outputFile);
            break;
        case 's':
            sFlag(inputFile, outputFile);
            break;
        case 'a':
            aFlag(inputFile, outputFile);
            break;
        default:
            fclose(inputFile);
            fclose(outputFile);
            return UNKNOWN_FLAG;
    }

    fclose(inputFile);
    fclose(outputFile);
    return OK;
}