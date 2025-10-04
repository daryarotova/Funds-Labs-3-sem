#ifndef CHECKING_H
#define CHECKING_H

#include "errors.h"

errorCodes isRightDoubleNum(const char *str); // проверяет, является ли строка корректным числом с плавающей точкой
errorCodes isRightIntNum(const char *str); // проверяет, является ли строка корректным целым числом

#endif // CHECKING_H
