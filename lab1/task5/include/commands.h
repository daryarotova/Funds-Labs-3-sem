#ifndef COMMANDS_H
#define COMMANDS_H

typedef enum {
    OK = 0,
    INVALID_ARGUMENT = 1,
    OUT_OF_RANGE = 2,
    NO_RESULT = 3,
    OVERFLOW = 4,
    IO_ERROR = 5,
    UNKNOWN_FLAG = 6,
    INVALID_FLAG_FORMAT = 7
} errorCodes;

typedef struct {
    char inputFilePath[256];
    char outputFilePath[256]; 
    char flag[4]; // 3 символа + '\0'
    int hasFileOutput; // если есть флаг n, то выходной файл - 3ий аргумент; есть нет, то имя файла генерируется добавлением префикса 'out_'
} commandLineArgs;

errorCodes parseCommandLine(int argc, char* argv[], commandLineArgs* args);
errorCodes validateFile(const char* path);
errorCodes validateFlag(const char* flag);
errorCodes processFile(const commandLineArgs* args);

#endif // COMMANDS_H