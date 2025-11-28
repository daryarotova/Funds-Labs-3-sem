#include "../include/file_operations.h"
#include "../include/liver.h"
#include "../include/linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int compare_livers_by_age(const Liver* l1, const Liver* l2) {
    if (l1->year != l2->year) {
        return l1->year - l2->year;
    }
    if (l1->month != l2->month) {
        return l1->month - l2->month;
    }
    return l1->day - l2->day;
}

void insert_sorted_by_age(LinkedList* list, Liver* liver) {
    if (!list || !liver) return;
    
    if (!list->head || compare_livers_by_age(liver, list->head->data) <= 0) {
        push_front_list(list, liver);
        return;
    }
    
    if (compare_livers_by_age(liver, list->tail->data) >= 0) {
        push_back_list(list, liver);
        return;
    }
    
    Node* current = list->head;
    size_t index = 0;
    
    while (current && compare_livers_by_age(liver, current->data) > 0) {
        current = current->next;
        index++;
    }
    
    insert_at_list(list, index, liver);
}

void sort_by_age(LinkedList* list) {
    if (!list || list->size <= 1) return;
    
    LinkedList sorted = create_list();
    Node* current = list->head;
    
    while (current) {
        Liver* copy = liver_copy(current->data);
        if (copy) {
            insert_sorted_by_age(&sorted, copy);
        }
        current = current->next;
    }
    
    erase_list(list);
    *list = sorted;
}

int load_from_file(const char* filename, LinkedList* list) {
    if (!filename || !list) return 0;
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }
    
    unsigned int id;
    char surname[100], name[100], patronymic[100];
    int day, month, year;
    char gender;
    double income;
    
    int line = 0;
    int loaded_count = 0;
    
    while (1) {
        if (fscanf(file, "%u %s %s", &id, surname, name) != 3) {
            break;
        }
        line++;
        
        char next_field[100];
        if (fscanf(file, "%s", next_field) != 1) {
            printf("Warning: Incomplete data at line %d, skipping.\n", line);
            break;
        }
        
        char* end_ptr;
        long potential_day = strtol(next_field, &end_ptr, 10);
        
        if (*end_ptr == '\0') {
            day = (int)potential_day;
            strcpy(patronymic, "");
        } else {
            strcpy(patronymic, next_field);
            if (fscanf(file, "%d", &day) != 1) {
                printf("Warning: Incomplete data at line %d, skipping.\n", line);
                break;
            }
        }
        
        if (fscanf(file, "%d %d %c %lf", &month, &year, &gender, &income) != 4) {
            printf("Warning: Incomplete data at line %d, skipping.\n", line);
            continue;
        }
        
        if (!liver_validate_id(id) || !liver_validate_name(surname) || 
            !liver_validate_name(name) || !liver_validate_date(day, month, year) ||
            !liver_validate_gender(gender) || !liver_validate_income(income)) {
            printf("Warning: Invalid data at line %d, skipping.\n", line);
            continue;
        }
        
        if (strlen(patronymic) > 0 && !liver_validate_name(patronymic)) {
            printf("Warning: Invalid patronymic at line %d, skipping.\n", line);
            continue;
        }
        
        Liver* new_liver = NULL;
        if (liver_create(&new_liver, id, surname, name, patronymic,
                        day, month, year, gender, income)) {
            insert_sorted_by_age(list, new_liver);
            loaded_count++;
        } else {
            printf("Warning: Failed to create liver at line %d\n", line);
        }
    }
    
    fclose(file);
    printf("Loaded %d livers from %s\n", loaded_count, filename);
    return 1;
}

int save_to_file(const char* filename, const LinkedList* list) {
    if (!filename || !list) return 0;
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot create file %s\n", filename);
        return 0;
    }
    
    Node* current = list->head;
    while (current) {
        Liver* liver = current->data;
        fprintf(file, "%u %s %s %s %d %d %d %c %.2f\n",
                liver->id, liver->surname, liver->name, 
                strlen(liver->patronymic) > 0 ? liver->patronymic : "",
                liver->day, liver->month, liver->year, 
                liver->gender, liver->income);
        current = current->next;
    }
    
    fclose(file);
    printf("Saved %zu livers to %s\n", list->size, filename);
    return 1;
}

void print_all_livers(const LinkedList* list) {
    if (!list) {
        printf("Invalid list\n");
        return;
    }
    
    if (list->size == 0) {
        printf("No livers in the list\n");
        return;
    }
    
    printf("=== Livers (%zu total) ===\n", list->size);
    Node* current = list->head;
    size_t count = 0;
    
    while (current) {
        printf("%zu. ", ++count);
        liver_print(current->data);
        current = current->next;
    }
}