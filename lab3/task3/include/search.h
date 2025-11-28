#ifndef SEARCH_H
#define SEARCH_H

#include "linked_list.h"

Node* search_by_id(const LinkedList* list, unsigned int id);
size_t search_index_by_id(const LinkedList* list, unsigned int id);
Node* search_by_full_name(const LinkedList* list, const char* surname, const char* name);
LinkedList* search_by_surname(const LinkedList* list, const char* surname);
LinkedList* search_by_gender(const LinkedList* list, char gender);
LinkedList* search_by_birth_year(const LinkedList* list, int year);
LinkedList* search_by_income_range(const LinkedList* list, double min_income, double max_income);

LinkedList* search_by_criteria(const LinkedList* list, 
                              const char* surname, 
                              char gender, 
                              int min_age, 
                              int max_age);

void search_results_free(LinkedList* results);
void search_results_print(const LinkedList* results);

#endif