#include "../include/solve.h"
#include "../include/output.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Ошибка: неверное количество аргументов.\n\n");
        printTableOfInstructions();
        return 1;
    }

    const char* inputPath = argv[1];
    const char* outputPath = argv[2];

    FILE* inputFile = fopen(inputPath, "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Ошибка: не удалось открыть входной файл: %s\n", inputPath);
        return 1;
    }

    FILE* outputFile = fopen(outputPath, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Ошибка: не удалось открыть выходной файл: %s\n", outputPath);
        fclose(inputFile);
        return 1;
    }

    errorCodes status = solve(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    if (status != OK) {
        switch (status) {
            case INVALID_ARGUMENT:
                fprintf(stderr, "Ошибка: неверные аргументы функции.\n");
                break;
            case PARSE_ERROR:
                fprintf(stderr, "Ошибка: невозможно распознать число в файле.\n");
                break;
            case OVERFLOW:
                fprintf(stderr, "Ошибка: переполнение при вычислении значения числа.\n");
                break;
            case IO_ERROR:
                fprintf(stderr, "Ошибка: ошибка ввода/вывода при работе с файлами.\n");
                break;
            case NO_MEMORY:
                fprintf(stderr, "Ошибка: недостаточно памяти.\n");
                break;
            default:
                fprintf(stderr, "Неизвестная ошибка.\n");
                break;
        }

        fprintf(stderr, "\n");
        printTableOfInstructions();
        return 1;
    }

    return 0;
}