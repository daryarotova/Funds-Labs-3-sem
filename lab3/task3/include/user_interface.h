#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "application.h"

void run_application(void);

void show_main_menu(void);
void show_search_menu(void);
void show_edit_menu(void);

int get_choice(int min, int max);
void get_string_input(char* buffer, size_t size, const char* prompt);
int get_int_input(const char* prompt);
double get_double_input(const char* prompt);
void get_date_input(int* day, int* month, int* year);

#endif