#include "../include/liver.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

static char* copy_string(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str) + 1;
    char* copy = malloc(len);
    if (copy) {
        strcpy(copy, str);
    }
    return copy;
}

int liver_validate_date(int day, int month, int year) {
    if (year < 1900 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    
    int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
        days_in_month[1] = 29;
    }
    
    return (day >= 1 && day <= days_in_month[month-1]);
}

int liver_validate_name(const char* name) {
    if (!name || strlen(name) == 0) return 0;
    
    for (size_t i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i])) return 0;
    }
    return 1;
}

int liver_validate_gender(char gender) {
    return (gender == 'M' || gender == 'W');
}

int liver_validate_income(double income) {
    return (income >= 0.0);
}

int liver_validate_id(unsigned int id) {
    return (id > 0);
}

int liver_validate(const Liver* liver) {
    if (!liver) return 0;
    
    return liver_validate_id(liver->id) &&
           liver_validate_name(liver->surname) &&
           liver_validate_name(liver->name) &&
           liver_validate_name(liver->patronymic) &&
           liver_validate_date(liver->day, liver->month, liver->year) &&
           liver_validate_gender(liver->gender) &&
           liver_validate_income(liver->income);
}

int liver_create(Liver** liver, unsigned int id, const char* surname, 
                const char* name, const char* patronymic, int day, 
                int month, int year, char gender, double income) {
    if (!liver) return 0;
    
    if (!liver_validate_id(id) || !liver_validate_name(surname) || 
        !liver_validate_name(name) || !liver_validate_date(day, month, year) ||
        !liver_validate_gender(gender) || !liver_validate_income(income)) {
        return 0;
    }
    
    if (patronymic && strlen(patronymic) > 0 && !liver_validate_name(patronymic)) {
        return 0;
    }
    
    *liver = (Liver*)malloc(sizeof(Liver));
    if (!*liver) return 0;
    
    (*liver)->id = id;
    
    (*liver)->surname = copy_string(surname);
    (*liver)->name = copy_string(name);
    (*liver)->patronymic = (patronymic && strlen(patronymic) > 0) ? copy_string(patronymic) : copy_string("");
    
    if (!(*liver)->surname || !(*liver)->name || !(*liver)->patronymic) {
        liver_free(*liver);
        *liver = NULL;
        return 0;
    }
    
    (*liver)->day = day;
    (*liver)->month = month;
    (*liver)->year = year;
    (*liver)->gender = gender;
    (*liver)->income = income;
    
    return 1;
}

Liver* liver_copy(const Liver* src) {
    if (!src) return NULL;
    
    Liver* copy = NULL;
    if (!liver_create(&copy, src->id, src->surname, src->name, src->patronymic,
                     src->day, src->month, src->year, src->gender, src->income)) {
        return NULL;
    }
    return copy;
}

void liver_free(Liver* liver) {
    if (!liver) return;
    
    free(liver->surname);
    free(liver->name);
    free(liver->patronymic);
    free(liver);
}

int liver_calculate_age(const Liver* liver) {
    if (!liver) return -1;
    
    time_t now = time(NULL);
    struct tm* local_time = localtime(&now);
    int current_year = local_time->tm_year + 1900;
    int current_month = local_time->tm_mon + 1;
    int current_day = local_time->tm_mday;
    
    int age = current_year - liver->year;
    
    if (current_month < liver->month || 
        (current_month == liver->month && current_day < liver->day)) {
        age--;
    }
    
    return age;
}

void liver_print(const Liver* liver) {
    if (!liver) {
        printf("Invalid liver data\n");
        return;
    }
    
    printf("ID: %u\n", liver->id);
    printf("Name: %s %s %s\n", liver->surname, liver->name, 
           strlen(liver->patronymic) > 0 ? liver->patronymic : "(no patronymic)");
    printf("Birth date: %02d.%02d.%d\n", liver->day, liver->month, liver->year);
    printf("Age: %d years\n", liver_calculate_age(liver));
    printf("Gender: %c\n", liver->gender);
    printf("Income: %.2f\n", liver->income);
    printf("---\n");
}

char* liver_date_to_string(const Liver* liver) {
    if (!liver) return NULL;
    
    char* date_str = (char*)malloc(11); // DD.MM.YYYY + null terminator
    if (!date_str) return NULL;
    
    snprintf(date_str, 11, "%02d.%02d.%04d", liver->day, liver->month, liver->year);
    return date_str;
}
