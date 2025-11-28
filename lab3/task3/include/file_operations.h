#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "linked_list.h"
#include "liver.h"

int load_from_file(const char* filename, LinkedList* list);
int save_to_file(const char* filename, const LinkedList* list);

void sort_by_age(LinkedList* list);
void insert_sorted_by_age(LinkedList* list, Liver* liver);

void print_all_livers(const LinkedList* list);

#endif