#include "../include/user_interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void run_application(void) {
    AppState state;
    app_init(&state);
    
    printf("=== Liver Management System ===\n");
    printf("Welcome to the program!\n");
    
    int choice;
    do {
        show_main_menu();
        choice = get_choice(0, 8);
        
        switch (choice) {
            case 1:
                app_load_file(&state);
                break;
            case 2:
                app_save_file(&state);
                break;
            case 3:
                app_add_liver(&state);
                break;
            case 4:
                app_edit_liver(&state);
                break;
            case 5:
                app_delete_liver(&state);
                break;
            case 6:
                app_search_liver(&state);
                break;
            case 7:
                app_undo(&state);
                break;
            case 8:
                app_print_all(&state);
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice\n");
        }
        
        printf("\n");
    } while (choice != 0);
    
    app_cleanup(&state);
}

void show_main_menu(void) {
    printf("\n=== Main Menu ===\n");
    printf("1. Load from file\n");
    printf("2. Save to file\n");
    printf("3. Add liver\n");
    printf("4. Edit liver\n");
    printf("5. Delete liver\n");
    printf("6. Search liver\n");
    printf("7. Undo last N/2 modifications\n");
    printf("8. Print all livers\n");
    printf("0. Exit\n");
    printf("Choose option: ");
}

void show_search_menu(void) {
    printf("\n=== Search Menu ===\n");
    printf("1. Search by ID\n");
    printf("2. Search by surname\n");
    printf("3. Search by full name\n");
    printf("4. Search by gender\n");
    printf("5. Search by birth year\n");
    printf("6. Search by income range\n");
    printf("7. Combined search\n");
    printf("0. Back to main menu\n");
}

void show_edit_menu(void) {
    printf("\n=== Edit Menu ===\n");
    printf("1. Edit surname\n");
    printf("2. Edit name\n");
    printf("3. Edit patronymic\n");
    printf("4. Edit birth date\n");
    printf("5. Edit gender\n");
    printf("6. Edit income\n");
    printf("0. Finish editing\n");
}

int get_choice(int min, int max) {
    int choice;
    while (scanf("%d", &choice) != 1 || choice < min || choice > max) {
        printf("Invalid input. Please enter a number between %d and %d: ", min, max);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    return choice;
}

void get_string_input(char* buffer, size_t size, const char* prompt) {
    (void)size;
    printf("%s", prompt);
    scanf("%s", buffer);
}

int get_int_input(const char* prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        printf("Invalid input. Please enter an integer: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    return value;
}

double get_double_input(const char* prompt) {
    double value;
    printf("%s", prompt);
    while (scanf("%lf", &value) != 1) {
        printf("Invalid input. Please enter a number: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    return value;
}

void get_date_input(int* day, int* month, int* year) {
    printf("Enter date (day month year): ");
    while (scanf("%d %d %d", day, month, year) != 3) {
        printf("Invalid input. Please enter three numbers (day month year): ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}