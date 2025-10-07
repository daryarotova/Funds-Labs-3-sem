#ifndef NUMBER_LN2_H
#define NUMBER_LN2_H

#include "constants.h"

errorCodes limitLn2(double epsilon, double* result);
errorCodes seriesLn2(double epsilon, double* result);
errorCodes equationLn2(double epsilon, double* result);

#endif