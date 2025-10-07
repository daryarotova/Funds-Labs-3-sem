#include <stdio.h>

#include "include/number_e.h"
#include "include/number_gamma.h"
#include "include/number_ln2.h"
#include "include/number_pi.h"
#include "include/number_sqrt2.h"
#include "include/functions.h"

void printResult(const char* constantName, errorCodes status1, double result1, 
                 errorCodes status2, double result2, errorCodes status3, double result3) {
    printf("%s: ", constantName);
    
    if (status1 == OK) {
        printf("%.10f", result1);
    } else {
        printf("ERROR(%d)", status1);
    }
    
    printf(", ");
    
    if (status2 == OK) {
        printf("%.10f", result2);
    } else {
        printf("ERROR(%d)", status2);
    }
    
    printf(", ");
    
    if (status3 == OK) {
        printf("%.10f", result3);
    } else {
        printf("ERROR(%d)", status3);
    }
    
    printf("\n");
}

int main() {
    const double EPSILON = 0.00000001;
    double result1 = 0.0;
    double result2 = 0.0;
    double result3 = 0.0;
    errorCodes status1 = OK;
    errorCodes status2 = OK;
    errorCodes status3 = OK;

    printf("Точность равна %.8lf\n\n", EPSILON);

    status1 = limitE(EPSILON, &result1);
    status2 = seriesE(EPSILON, &result2);
    status3 = equationE(EPSILON, &result3);
    printResult("Число е", status1, result1, status2, result2, status3, result3);

    status1 = limitPi(EPSILON, &result1);
    status2 = seriesPi(EPSILON, &result2);
    status3 = equationPi(EPSILON, &result3);
    printResult("Число Пи", status1, result1, status2, result2, status3, result3);

    status1 = limitLn2(EPSILON, &result1);
    status2 = seriesLn2(EPSILON, &result2);
    status3 = equationLn2(EPSILON, &result3);
    printResult("Число ln(2)", status1, result1, status2, result2, status3, result3);

    status1 = limitSqrt2(EPSILON, &result1);
    status2 = seriesSqrt2(EPSILON, &result2);
    status3 = equationSqrt2(EPSILON, &result3);
    printResult("Число sqrt(2)", status1, result1, status2, result2, status3, result3);

    status1 = limitGamma(EPSILON, &result1);
    status2 = seriesGamma(EPSILON, &result2);
    status3 = equationGamma(EPSILON, &result3);
    printResult("Число gamma", status1, result1, status2, result2, status3, result3);

    return OK;
}