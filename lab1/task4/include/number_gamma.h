#ifndef NUMBER_GAMMA_H
#define NUMBER_GAMMA_H

#include "constants.h"

errorCodes limitGamma(double epsilon, double* result);
errorCodes seriesGamma(double epsilon, double* result);
errorCodes equationGamma(double epsilon, double* result);

#endif