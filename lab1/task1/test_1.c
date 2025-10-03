#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Функция для запуска команды и считывания её вывода
int runCmd(const char *cmd, const char *expectedOutput) {
    char buf[BUFFER_SIZE];
    FILE *fp;
    // int result = 1; fail по умолчанию

    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Ошибка при запуске команды: %s\n", cmd);
        return 0;
    }

    buf[0] = '\0';
    while (fgets(buf + strlen(buf), sizeof(buf) - strlen(buf), fp) != NULL) {}

    pclose(fp);

    // Убираем символ конца строки
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    }

    if (strcmp(buf, expectedOutput) == 0) {
        return 1; // PASS
    } else {
        printf("Провалилось: %s\nОжидалось: \"%s\"\nПолучилось:      \"%s\"\n\n", cmd, expectedOutput, buf);
        return 0; // FAIL
    }
}

int main() {
    int passCount = 0;

    // Тесты на количество аргументов
    passCount += runCmd("./task_1.a", "Некорректное количество аргументов");
    passCount += runCmd("./task_1.a 1 2 3", "Некорректное количество аргументов");

    // Тесты на некорректный ввод
    passCount += runCmd("./task_1.a abc -h", "Некорректный ввод");
    passCount += runCmd("./task_1.a -5 -f", "Некорректный ввод");

    // Флаг -h
    passCount += runCmd("./task_1.a 5 -h", "5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100");

    // Флаг -p
    passCount += runCmd("./task_1.a 11 -p", "Число 11 является простым.");

    // Флаг -s
    passCount += runCmd("./task_1.a 254 -s", "F E");

    // Флаг -e
    passCount += runCmd("./task_1.a 3 -e",
        "Таблица степеней (основания 1-10, степени 1-3):\n"
        " 1: 1 1 1\n"
        " 2: 2 4 8\n"
        " 3: 3 9 27\n"
        " 4: 4 16 64\n"
        " 5: 5 25 125\n"
        " 6: 6 36 216\n"
        " 7: 7 49 343\n"
        " 8: 8 64 512\n"
        " 9: 9 81 729\n"
        "10: 10 100 1000"
    );

    // Флаг -a
    passCount += runCmd("./task_1.a 10 -a", "55");

    // Флаг -f
    passCount += runCmd("./task_1.a 4 -f", "24");

    // Флаг -e out of range
    passCount += runCmd("./task_1.a 25 -e", "Ошибка: для флага -e число x должно быть в диапазоне от 1 до 10 включительно.");

    printf("\nРезультат тестов: \n");
    printf("Успешные тесты: %d из 11. \n", passCount);

    return 0;
}
