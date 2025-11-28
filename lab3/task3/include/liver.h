#ifndef LIVER_H
#define LIVER_H

#include <stddef.h>

typedef struct {
    unsigned int id;
    char* surname;
    char* name; 
    char* patronymic;
    int day;
    int month;
    int year;
    char gender;
    double income;
} Liver;

int liver_create(Liver** liver, unsigned int id, const char* surname, 
                const char* name, const char* patronymic, int day, 
                int month, int year, char gender, double income);

int liver_validate(const Liver* liver);
int liver_validate_date(int day, int month, int year);
int liver_validate_name(const char* name);
int liver_validate_gender(char gender);
int liver_validate_income(double income);
int liver_validate_id(unsigned int id);

void liver_free(Liver* liver);
Liver* liver_copy(const Liver* src);
int liver_calculate_age(const Liver* liver);
void liver_print(const Liver* liver);
char* liver_date_to_string(const Liver* liver);

#endif