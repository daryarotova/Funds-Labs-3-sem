#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    OK = 0, // корректный ввод
    INVALID_ARGUMENT = 1, // строка не является числом
    OUT_RANGE = 2, // выход за допустимый диапазон
    NO_RESULT = 3, // результат не может быть посчитан
    OVERFLOW = 4, // переполнение
    IO_ERROR = 5, // ошибка ввода/вывода
    UNKNOWN_FLAG = 6 // неизвестный флаг
} errorCodes;

#endif // ERRORS_H