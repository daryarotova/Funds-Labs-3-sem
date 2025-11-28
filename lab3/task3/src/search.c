#include "../include/search.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

Node* search_by_id(const LinkedList* list, unsigned int id) {
    if (!list || id == 0) return NULL;
    
    Node* current = list->head;
    while (current) {
        if (current->data->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

size_t search_index_by_id(const LinkedList* list, unsigned int id) {
    if (!list) return (size_t)-1;
    size_t index = 0;
    Node* current = list->head;
    while (current) {
        if (current->data->id == id)
            return index;
        current = current->next;
        index++;
    }
    return (size_t)-1;
}

Node* search_by_full_name(const LinkedList* list, const char* surname, const char* name) {
    if (!list || !surname || !name) return NULL;
    
    Node* current = list->head;
    while (current) {
        Liver* liver = current->data;
        if (strcmp(liver->surname, surname) == 0 && 
            strcmp(liver->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

LinkedList* search_by_surname(const LinkedList* list, const char* surname) {
    if (!list || !surname) return NULL;
    
    LinkedList* results = (LinkedList*)malloc(sizeof(LinkedList));
    if (!results) return NULL;
    *results = create_list();
    
    Node* current = list->head;
    while (current) {
        Liver* liver = current->data;
        if (strcmp(liver->surname, surname) == 0) {
            Liver* copy = liver_copy(liver);
            if (copy) {
                push_back_list(results, copy);
            }
        }
        current = current->next;
    }
    
    return results;
}

LinkedList* search_by_gender(const LinkedList* list, char gender) {
    if (!list || !liver_validate_gender(gender)) return NULL;
    
    LinkedList* results = (LinkedList*)malloc(sizeof(LinkedList));
    if (!results) return NULL;
    *results = create_list();
    
    Node* current = list->head;
    while (current) {
        Liver* liver = current->data;
        if (liver->gender == gender) {
            Liver* copy = liver_copy(liver);
            if (copy) {
                push_back_list(results, copy);
            }
        }
        current = current->next;
    }
    
    return results;
}

LinkedList* search_by_birth_year(const LinkedList* list, int year) {
    if (!list || year < 1900 || year > 2100) return NULL;
    
    LinkedList* results = (LinkedList*)malloc(sizeof(LinkedList));
    if (!results) return NULL;
    *results = create_list();
    
    Node* current = list->head;
    while (current) {
        Liver* liver = current->data;
        if (liver->year == year) {
            Liver* copy = liver_copy(liver);
            if (copy) {
                push_back_list(results, copy);
            }
        }
        current = current->next;
    }
    
    return results;
}

LinkedList* search_by_income_range(const LinkedList* list, double min_income, double max_income) {
    if (!list || min_income < 0 || max_income < 0 || min_income > max_income) {
        return NULL;
    }
    
    LinkedList* results = (LinkedList*)malloc(sizeof(LinkedList));
    if (!results) return NULL;
    *results = create_list();
    
    Node* current = list->head;
    while (current) {
        Liver* liver = current->data;
        if (liver->income >= min_income && liver->income <= max_income) {
            Liver* copy = liver_copy(liver);
            if (copy) {
                push_back_list(results, copy);
            }
        }
        current = current->next;
    }
    
    return results;
}

LinkedList* search_by_criteria(const LinkedList* list, 
                              const char* surname, 
                              char gender, 
                              int min_age, 
                              int max_age) {
    if (!list) return NULL;
    
    LinkedList* results = (LinkedList*)malloc(sizeof(LinkedList));
    if (!results) return NULL;
    *results = create_list();
    
    Node* current = list->head;
    while (current) {
        Liver* liver = current->data;
        int matches = 1;
        
        if (surname && strlen(surname) > 0) {
            if (strcmp(liver->surname, surname) != 0) {
                matches = 0;
            }
        }
        
        if (matches && liver_validate_gender(gender)) {
            if (liver->gender != gender) {
                matches = 0;
            }
        }
        
        if (matches && min_age >= 0 && max_age >= min_age) {
            int age = liver_calculate_age(liver);
            if (age < min_age || age > max_age) {
                matches = 0;
            }
        }
        
        if (matches) {
            Liver* copy = liver_copy(liver);
            if (copy) {
                push_back_list(results, copy);
            }
        }
        
        current = current->next;
    }
    
    return results;
}

void search_results_free(LinkedList* results) {
    if (!results) return;
    delete_list(results);
    free(results);
}

void search_results_print(const LinkedList* results) {
    if (!results || results->size == 0) {
        printf("No results found\n");
        return;
    }
    
    printf("=== Search Results (%zu found) ===\n", results->size);
    Node* current = results->head;
    size_t count = 0;
    
    while (current) {
        printf("%zu. ", ++count);
        liver_print(current->data);
        current = current->next;
    }
}