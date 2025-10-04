#ifndef OUTPUTING_H
#define OUTPUTING_H

#include "errors.h"

errorCodes printTableWithInstructions(void); // инструкция дл пользователя
errorCodes printQuadraticSolution(const double *roots, int precision, double a, double b, double c); // на вывод квадратное уравнение и его корни

#endif // OUTPUTING_H
