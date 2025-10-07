#ifndef FUNCTIONS_H
#define FUNCTIONS_H

double functionA(double x, double epsilon);
double functionB(double x, double epsilon);
double functionC(double x, double epsilon);
double functionD(double x, double epsilon);

double calculateIntegral(double (*function)(double, double), double epsilon, double a, double b);

#endif
