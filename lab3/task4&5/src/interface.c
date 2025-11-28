#include "../include/interface.h"
#include "../include/mail_system.h"
#include "../include/heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t auto_process = 0;

void handle_signal(int sig) {
    if (sig == SIGINT) {
        auto_process = 0;
    }
}

void sleep_ms(int milliseconds) {
    for (int i = 0; i < milliseconds * 1000; i++) {
    }
}

void print_offices_info(MailSystem *system) {
    printf("\n=== Информация об отделениях ===\n");
    for (size_t i = 0; i < system->offices_count; i++) {
        MailOffice *office = &system->offices[i];
        printf("Отделение %d: вместимость = %d, писем = %zu, связей = %zu [",
               office->id, office->capacity, 
               office->letter_heap.size, office->connected_count);
        
        for (size_t j = 0; j < office->connected_count; j++) {
            printf("%d", office->connected_offices[j]);
            if (j < office->connected_count - 1) printf(", ");
        }
        printf("]\n");
    }
    printf("================================\n");
}

void print_letters_status(MailSystem *system) {
    printf("\n=== Статусы писем ===\n");
    for (size_t i = 0; i < system->letters_count; i++) {
        Letter *letter = &system->letters[i];
        const char *status_str;
        switch (letter->status) {
            case STATUS_IN_TRANSIT: status_str = "В ПУТИ"; break;
            case STATUS_DELIVERED: status_str = "ДОСТАВЛЕНО"; break;
            case STATUS_UNDELIVERED: status_str = "НЕ ДОСТАВЛЕНО"; break;
            default: status_str = "НЕИЗВЕСТНО";
        }
        printf("Письмо %d: %s (из %d в %d, сейчас в %d)\n", 
               letter->id, status_str, 
               letter->from_office_id, letter->to_office_id, letter->current_office_id);
    }
    printf("=====================\n");
}

void print_menu() {
    printf("\n=== Почтовый Сервис ===\n");
    printf("1. Добавить почтовое отделение\n");
    printf("2. Удалить почтовое отделение\n");
    printf("3. Добавить письмо\n");
    printf("4. Пометить письмо как недоставленное\n");
    printf("5. Забрать письмо\n");
    printf("6. Показать все письма\n");
    printf("7. Обработать письма (автоматически)\n");
    printf("8. Показать информацию об отделениях\n");
    printf("9. Показать информацию о письмах\n");
    printf("10. Выход\n");
    printf("Выберите действие: ");
}

void load_mappings(MailSystem *system, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл маппингов: %s\n", filename);
        return;
    }
    
    printf("Чтение файла маппингов: %s\n", filename);
    
    int office1, office2;
    int line_count = 0;
    
    while (fscanf(file, "%d %d", &office1, &office2) == 2) {
        printf("Строка %d: %d <-> %d\n", ++line_count, office1, office2);
        
        if (!find_office(system, office1)) {
            int empty_conn[] = {0};
            if (add_mail_office(system, office1, 10, empty_conn, 0)) {
                printf("Создано отделение %d\n", office1);
            } else {
                printf("Ошибка создания отделения %d\n", office1);
            }
        }
        
        if (!find_office(system, office2)) {
            int empty_conn[] = {0};
            if (add_mail_office(system, office2, 10, empty_conn, 0)) {
                printf("Создано отделение %d\n", office2);
            } else {
                printf("Ошибка создания отделения %d\n", office2);
            }
        }
    }
    
    if (line_count == 0) {
        printf("Файл маппингов пуст или имеет неверный формат\n");
        fclose(file);
        return;
    }
    
    rewind(file);
    
    printf("Установка связей между отделениями.\n");
    
    while (fscanf(file, "%d %d", &office1, &office2) == 2) {
        MailOffice *office1_ptr = find_office(system, office1);
        MailOffice *office2_ptr = find_office(system, office2);
        
        if (office1_ptr && office2_ptr) {
            int *new_conn1 = realloc(office1_ptr->connected_offices, 
                                   (office1_ptr->connected_count + 1) * sizeof(int));
            if (new_conn1) {
                office1_ptr->connected_offices = new_conn1;
                office1_ptr->connected_offices[office1_ptr->connected_count] = office2;
                office1_ptr->connected_count++;
                printf("Добавлена связь: %d -> %d\n", office1, office2);
            }
            
            int *new_conn2 = realloc(office2_ptr->connected_offices, 
                                   (office2_ptr->connected_count + 1) * sizeof(int));
            if (new_conn2) {
                office2_ptr->connected_offices = new_conn2;
                office2_ptr->connected_offices[office2_ptr->connected_count] = office1;
                office2_ptr->connected_count++;
                printf("Добавлена связь: %d -> %d\n", office2, office1);
            }
        }
    }
    
    fclose(file);
    printf("Загружены маппинги из файла: %s\n", filename);
    printf("Создано %zu отделений\n", system->offices_count);
}

void auto_process_letters(MailSystem *system) {
    printf("Автоматическая обработка включена\n");
    printf("Для остановки нажмите Ctrl+C\n");
    
    int iteration = 0;
    while (auto_process) {
        printf("Итерация обработки %d...\n", ++iteration);
        process_letters(system);
        
        sleep_ms(200);
        
        int letters_in_transit = 0;
        for (size_t i = 0; i < system->letters_count; i++) {
            if (system->letters[i].status == STATUS_IN_TRANSIT) {
                letters_in_transit = 1;
                break;
            }
        }
        
        if (!letters_in_transit) {
            printf("Все письма обработаны. Автоматическая обработка завершена.\n");
            auto_process = 0;
        }
    }
    
    printf("Автоматическая обработка остановлена.\n");
}