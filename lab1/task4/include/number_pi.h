#ifndef NUMBER_PI_H
#define NUMBER_PI_H

#include "constants.h"

errorCodes limitPi(double epsilon, double* result);
errorCodes seriesPi(double epsilon, double* result);
errorCodes equationPi(double epsilon, double* result);

#endif