#include "../include/application.h"
#include "../include/file_operations.h"
#include "../include/liver.h"
#include "../include/search.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void app_init(AppState* state) {
    if (!state) return;
    
    state->livers = create_list();
    undo_init(&state->undo_manager);
}

void app_cleanup(AppState* state) {
    if (!state) return;
        
    undo_clear(&state->undo_manager);
    delete_list(&state->livers);

}

void app_load_file(AppState* state) {
    if (!state) return;
    
    char filename[256];
    printf("Enter filename to load: ");
    scanf("%255s", filename);
    
    erase_list(&state->livers);
    undo_clear(&state->undo_manager);
    
    if (load_from_file(filename, &state->livers)) {
        printf("File loaded successfully\n");
    } else {
        printf("Failed to load file\n");
    }
}

void app_save_file(AppState* state) {
    if (!state) return;
    
    char filename[256];
    printf("Enter filename to save: ");
    scanf("%255s", filename);
    
    if (save_to_file(filename, &state->livers)) {
        printf("File saved successfully\n");
    } else {
        printf("Failed to save file\n");
    }
}

void app_add_liver(AppState* state) {
    if (!state) return;
    
    printf("=== Add New Liver ===\n");
    
    unsigned int id;
    char surname[100], name[100], patronymic[100];
    int day, month, year;
    char gender;
    double income;
    
    printf("ID: ");
    scanf("%u", &id);
    
    if (search_by_id(&state->livers, id)) {
        printf("Error: Liver with ID %u already exists\n", id);
        return;
    }
    
    printf("Surname: ");
    scanf("%99s", surname);
    printf("Name: ");
    scanf("%99s", name);

    printf("Patronymic (press Enter for none): ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char patronymic_input[100];
    if (fgets(patronymic_input, sizeof(patronymic_input), stdin)) {
        size_t len = strlen(patronymic_input);
        if (len > 0 && patronymic_input[len-1] == '\n') {
            patronymic_input[len-1] = '\0';
        }
        if (strlen(patronymic_input) == 0 || strcmp(patronymic_input, "-") == 0) {
            strcpy(patronymic, "");
        } else {
            strcpy(patronymic, patronymic_input);
        }
    } else {
        strcpy(patronymic, "");
    }

    printf("Birth day: ");
    scanf("%d", &day);
    printf("Birth month: ");
    scanf("%d", &month);
    printf("Birth year: ");
    scanf("%d", &year);
    printf("Gender (M/W): ");
    scanf(" %c", &gender);
    printf("Income: ");
    scanf("%lf", &income);
    
    if (!liver_validate_id(id) || !liver_validate_name(surname) || 
        !liver_validate_name(name) || !liver_validate_date(day, month, year) ||
        !liver_validate_gender(gender) || !liver_validate_income(income)) {
        printf("Error: Invalid input data\n");
        return;
    }
    
    Liver* new_liver = NULL;
    if (liver_create(&new_liver, id, surname, name, 
                    strcmp(patronymic, "-") == 0 ? "" : patronymic,
                    day, month, year, gender, income)) {
        
        size_t index = 0;
        Node* current = state->livers.head;
        while (current && liver_calculate_age(current->data) < liver_calculate_age(new_liver)) {
            current = current->next;
            index++;
        }
        
        insert_sorted_by_age(&state->livers, new_liver);
        undo_register_add(&state->undo_manager, new_liver, index);
        
        printf("Liver added successfully\n");
    } else {
        printf("Failed to create liver\n");
    }
}

void app_edit_liver(AppState* state) {
    if (state->livers.size == 0) {
        printf("\nNo livers available to edit.\n");
        return;
    }

    unsigned int target_id;
    printf("\nEnter ID of the liver to edit: ");
    scanf("%u", &target_id);
    while (getchar() != '\n');

    size_t index = search_index_by_id(&state->livers, target_id);
    if (index == (size_t)-1) {
        printf("Liver with ID %u not found.\n", target_id);
        return;
    }

    Liver* liver = get_at_list(&state->livers, index);
    if (!liver) {
        printf("Error: Failed to get the liver.\n");
        return;
    }

    printf("Editing liver with ID %u.\n", target_id);

    Liver* old_liver = liver_copy(liver);
    if (!old_liver) {
        printf("Error: Failed to copy liver for undo.\n");
        return;
    }

    printf("Enter new name (leave empty to keep '%s'): ", liver->name);
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(liver->name, buffer, sizeof(liver->name) - 1);
        liver->name[sizeof(liver->name) - 1] = '\0';
    }

    printf("Enter new surname (leave empty to keep '%s'): ", liver->surname);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(liver->surname, buffer, sizeof(liver->surname) - 1);
        liver->surname[sizeof(liver->surname) - 1] = '\0';
    }

    printf("Enter new patronymic (leave empty to keep '%s', '-' for none): ",
        liver->patronymic[0] ? liver->patronymic : "(none)");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "-") == 0) {
            liver->patronymic[0] = '\0';
        } else {
            strncpy(liver->patronymic, buffer, sizeof(liver->patronymic) - 1);
            liver->patronymic[sizeof(liver->patronymic) - 1] = '\0';
        }
    }

    printf("Enter new gender (M/W, leave empty to keep '%c'): ", liver->gender);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        char new_gender = buffer[0];

        if (liver_validate_gender(new_gender)) {
            liver->gender = new_gender;
        } else {
            printf("Invalid gender entered, keeping previous value.\n");
        }
    }


    printf("Enter new birth date (DD MM YYYY) or 0 to keep current (%02d %02d %d): ",
           liver->day, liver->month, liver->year);

    int nd, nm, ny;
    if (scanf("%d", &nd) == 1 && nd != 0) {
        scanf("%d %d", &nm, &ny);
        liver->day = nd;
        liver->month = nm;
        liver->year = ny;
    }
    while (getchar() != '\n');

    printf("Enter new income (leave empty to keep %.2f): ", liver->income);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        liver->income = atoi(buffer);
    }

    bool date_changed =
        liver->day   != old_liver->day ||
        liver->month != old_liver->month ||
        liver->year  != old_liver->year;

    if (date_changed) {
        Liver* to_reinsert = liver_copy(liver);
        if (!to_reinsert) {
            printf("Error: Failed to copy liver for reinsert\n");
            liver_free(old_liver);
            return;
        }

        delete_at_list(&state->livers, index);
        insert_sorted_by_age(&state->livers, to_reinsert);
    }

    undo_register_modify(&state->undo_manager, old_liver, index);
    printf("Liver updated successfully.\n");
}

void app_delete_liver(AppState* state) {
    if (!state) return;
    
    printf("=== Delete Liver ===\n");
    
    unsigned int id;
    printf("Enter liver ID to delete: ");
    scanf("%u", &id);
    
    Node* node = search_by_id(&state->livers, id);
    if (!node) {
        printf("Liver with ID %u not found\n", id);
        return;
    }
    
    printf("Liver to delete:\n");
    liver_print(node->data);
    
    size_t index = 0;
    Node* current = state->livers.head;
    while (current && current != node) {
        current = current->next;
        index++;
    }
    
    Liver* liver_copy_ptr = liver_copy(node->data);
    printf("Do you want to delete this liver? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        delete_at_list(&state->livers, index);
        undo_register_delete(&state->undo_manager, liver_copy_ptr, index);
        printf("Liver deleted successfully\n");
    } else {
        liver_free(liver_copy_ptr);
        printf("Deletion cancelled\n");
    }
}

void app_search_liver(AppState* state) {
    if (!state) return;
    
    printf("=== Search Liver ===\n");
    printf("1. Search by ID\n");
    printf("2. Search by surname\n"); 
    printf("3. Search by full name\n");
    printf("4. Search by gender\n");
    printf("5. Search by birth year\n");
    printf("6. Search by income range\n");
    printf("7. Combined search\n");
    printf("Choose option: ");
    
    int choice;
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: {
            unsigned int id;
            printf("Enter ID: ");
            scanf("%u", &id);
            Node* result = search_by_id(&state->livers, id);
            if (result) {
                printf("Found:\n");
                liver_print(result->data);
            } else {
                printf("Liver with ID %u not found\n", id);
            }
            break;
        }
        
        case 2: {
            char surname[100];
            printf("Enter surname: ");
            scanf("%99s", surname);
            LinkedList* results = search_by_surname(&state->livers, surname);
            if (results) {
                search_results_print(results);
                search_results_free(results);
            }
            break;
        }
        
        case 3: {
            char surname[100], name[100];
            printf("Enter surname: ");
            scanf("%99s", surname);
            printf("Enter name: ");
            scanf("%99s", name);
            Node* result = search_by_full_name(&state->livers, surname, name);
            if (result) {
                printf("Found:\n");
                liver_print(result->data);
            } else {
                printf("Liver not found\n");
            }
            break;
        }
        
        case 4: {
            char gender;
            printf("Enter gender (M/W): ");
            scanf(" %c", &gender);
            LinkedList* results = search_by_gender(&state->livers, gender);
            if (results) {
                search_results_print(results);
                search_results_free(results);
            }
            break;
        }
        
        case 5: {
            int year;
            printf("Enter birth year: ");
            scanf("%d", &year);
            LinkedList* results = search_by_birth_year(&state->livers, year);
            if (results) {
                search_results_print(results);
                search_results_free(results);
            }
            break;
        }
        
        case 6: {
            double min_income, max_income;
            printf("Enter min income: ");
            scanf("%lf", &min_income);
            printf("Enter max income: ");
            scanf("%lf", &max_income);
            LinkedList* results = search_by_income_range(&state->livers, min_income, max_income);
            if (results) {
                search_results_print(results);
                search_results_free(results);
            }
            break;
        }
        
        case 7: {
            char surname[100] = "", gender = '\0';
            int min_age = -1, max_age = -1;
            
            printf("Enter surname: ");
            scanf("%99s", surname);
            if (strlen(surname) == 0) surname[0] = '\0';
            
            printf("Enter gender: ");
            scanf(" %c", &gender);
            if (!liver_validate_gender(gender)) gender = '\0';
            
            printf("Enter min age (or -1 to skip): ");
            scanf("%d", &min_age);
            printf("Enter max age (or -1 to skip): ");
            scanf("%d", &max_age);
            
            LinkedList* results = search_by_criteria(&state->livers, 
                                                   strlen(surname) > 0 ? surname : NULL,
                                                   gender, min_age, max_age);
            if (results) {
                search_results_print(results);
                search_results_free(results);
            }
            break;
        }
        
        default:
            printf("Invalid choice\n");
    }
}

void app_undo(AppState* state) {
    if (!state) return;
    undo_last_half(&state->undo_manager, &state->livers);
}

void app_print_all(AppState* state) {
    if (!state) return;
    print_all_livers(&state->livers);
}