#include "include/commands.h"
#include "include/output.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    commandLineArgs args;
    errorCodes status;

    status = parseCommandLine(argc, argv, &args);
    if (status != OK) {
        switch (status) {
            case INVALID_ARGUMENT:
                printf("Неправильное количество аргументов\n");
                break;
            default:
                printf("Ошибка при разборе командной строки\n");
                break;
        }
        printTableOfInstructions();
        return status;
    }

    status = validateFlag(args.flag);
    if (status != OK) {
        switch (status) {
            case INVALID_FLAG_FORMAT:
                printf("Неверный формат флага\n");
                break;
            case UNKNOWN_FLAG:
                printf("Неизвестный флаг\n");
                break;
            default:
                printf("Ошибка при валидации флага\n");
                break;
        }
        printTableOfInstructions();
        return status;
    }

    status = validateFile(args.inputFilePath);
    if (status != OK) {
        switch (status) {
            case INVALID_ARGUMENT:
                printf("Неверный путь к файлу\n");
                break;
            case OUT_OF_RANGE:
                printf("Слишком длинный путь к файлу\n");
                break;
            case IO_ERROR:
                printf("Ошибка при открытии файла %s\n", args.inputFilePath);
                break;
            default:
                printf("Ошибка при валидации файла\n");
                break;
        }
        return status;
    }

    status = processFile(&args);
    if (status != OK) {
        printf("Ошибка при обработке файла\n");
        return status;
    }
    
    printf("Файл обработан успешно.\n");
    printf("Входной файл: %s\n", args.inputFilePath);
    printf("Выходной файл: %s\n", args.outputFilePath);
    printf("Флаг: %s\n", args.flag);
    
    return OK;
}