#include "../include/mail_system.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define INITIAL_CAPACITY 10

MailSystem create_mail_system() {
    MailSystem system;
    system.offices = NULL;
    system.offices_count = 0;
    system.offices_capacity = 0;
    system.letters = NULL;
    system.letters_count = 0;
    system.letters_capacity = 0;
    system.next_letter_id = 1;
    system.log_filename = NULL;
    return system;
}

void delete_mail_system(MailSystem *system) {
    if (!system) return;
    
    for (size_t i = 0; i < system->offices_count; i++) {
        delete_heap(&system->offices[i].letter_heap);
        free(system->offices[i].connected_offices);
    }
    free(system->offices);
    
    for (size_t i = 0; i < system->letters_count; i++) {
        free(system->letters[i].technical_data);
    }
    free(system->letters);
    
    free(system->log_filename);
}

MailOffice* find_office(MailSystem *system, int office_id) {
    for (size_t i = 0; i < system->offices_count; i++) {
        if (system->offices[i].id == office_id) {
            return &system->offices[i];
        }
    }
    return NULL;
}

Letter* find_letter(MailSystem *system, int letter_id) {
    for (size_t i = 0; i < system->letters_count; i++) {
        if (system->letters[i].id == letter_id) {
            return &system->letters[i];
        }
    }
    return NULL;
}

int is_office_connected(const MailOffice *office, int target_office_id) {
    for (size_t i = 0; i < office->connected_count; i++) {
        if (office->connected_offices[i] == target_office_id) {
            return 1;
        }
    }
    return 0;
}

int add_mail_office(MailSystem *system, int id, int capacity, const int *connected_offices, size_t connected_count) {
    if (!system || id < 0 || capacity <= 0 || find_office(system, id)) {
        return 0;
    }
    
    if (system->offices_count >= system->offices_capacity) {
        size_t new_capacity = system->offices_capacity == 0 ? INITIAL_CAPACITY : system->offices_capacity * 2;
        MailOffice *new_offices = realloc(system->offices, new_capacity * sizeof(MailOffice));
        if (!new_offices) return 0;
        system->offices = new_offices;
        system->offices_capacity = new_capacity;
    }
    
    MailOffice *office = &system->offices[system->offices_count];
    office->id = id;
    office->capacity = capacity;
    office->current_count = 0;
    office->letter_heap = create_heap(INITIAL_CAPACITY);
    office->connected_offices = malloc(connected_count * sizeof(int));
    office->connected_count = connected_count;
    
    if (!office->connected_offices) {
        delete_heap(&office->letter_heap);
        return 0;
    }
    
    memcpy(office->connected_offices, connected_offices, connected_count * sizeof(int));
    system->offices_count++;
    
    char log_msg[256];
    snprintf(log_msg, sizeof(log_msg), "Добавлено почтовое отделение %d с вместимостью %d", id, capacity);
    log_event(system, log_msg);
    
    return 1;
}

int remove_mail_office(MailSystem *system, int office_id) {
    if (!system) return 0;
    
    size_t office_index = system->offices_count;
    for (size_t i = 0; i < system->offices_count; i++) {
        if (system->offices[i].id == office_id) {
            office_index = i;
            break;
        }
    }
    
    if (office_index == system->offices_count) return 0;
    
    MailOffice *office = &system->offices[office_index];
    
    for (size_t i = 0; i < system->letters_count; i++) {
        Letter *letter = &system->letters[i];
        if (letter->from_office_id == office_id || letter->to_office_id == office_id) {
            letter->status = STATUS_UNDELIVERED;
        }
    }
    
    delete_heap(&office->letter_heap);
    free(office->connected_offices);
    
    for (size_t i = office_index; i < system->offices_count - 1; i++) {
        system->offices[i] = system->offices[i + 1];
    }
    system->offices_count--;
    
    char log_msg[256];
    snprintf(log_msg, sizeof(log_msg), "Удалено почтовое отделение %d", office_id);
    log_event(system, log_msg);
    
    return 1;
}

int add_letter(MailSystem *system, LetterType type, int priority, int from_office, int to_office, const char *tech_data) {
    if (!system || !tech_data) {
        printf("Ошибка: system или tech_data NULL\n");
        return 0;
    }
    
    MailOffice *from_office_ptr = find_office(system, from_office);
    if (!from_office_ptr) {
        printf("Ошибка: отделение отправителя %d не найдено\n", from_office);
        return 0;
    }
    
    MailOffice *to_office_ptr = find_office(system, to_office);
    if (!to_office_ptr) {
        printf("Ошибка: отделение получателя %d не найдено\n", to_office);
        return 0;
    }
    
    if (system->letters_count >= system->letters_capacity) {
        size_t new_capacity = system->letters_capacity == 0 ? INITIAL_CAPACITY : system->letters_capacity * 2;
        Letter *new_letters = realloc(system->letters, new_capacity * sizeof(Letter));
        if (!new_letters) {
            printf("Ошибка: не удалось выделить память для писем\n");
            return 0;
        }
        system->letters = new_letters;
        system->letters_capacity = new_capacity;
    }
    
    Letter *letter = &system->letters[system->letters_count];
    letter->id = system->next_letter_id++;
    letter->type = type;
    letter->status = STATUS_IN_TRANSIT;
    letter->priority = priority;
    letter->from_office_id = from_office;
    letter->to_office_id = to_office;
    letter->current_office_id = from_office;
    letter->technical_data = malloc(strlen(tech_data) + 1);
    
    if (!letter->technical_data) {
        printf("Ошибка: не удалось выделить память для технических данных\n");
        return 0;
    }
    strcpy(letter->technical_data, tech_data);
    
    push_heap(&from_office_ptr->letter_heap, -priority);
    from_office_ptr->current_count++;
    
    system->letters_count++;
    
    char log_msg[256];
    snprintf(log_msg, sizeof(log_msg), "Добавлено письмо %d из отделения %d в отделение %d", letter->id, from_office, to_office);
    log_event(system, log_msg);
    
    printf("Письмо %d успешно добавлено из отделения %d в отделение %d\n", 
           letter->id, from_office, to_office);
    
    return letter->id;
}

int mark_letter_undelivered(MailSystem *system, int letter_id) {
    if (!system) return 0;
    
    Letter *letter = find_letter(system, letter_id);
    if (!letter) return 0;
    
    letter->status = STATUS_UNDELIVERED;
    
    char log_msg[256];
    snprintf(log_msg, sizeof(log_msg), "Письмо %d помечено как недоставленное", letter_id);
    log_event(system, log_msg);
    
    return 1;
}

int pickup_letter(MailSystem *system, int letter_id) {
    if (!system) return 0;
    
    Letter *letter = find_letter(system, letter_id);
    if (!letter || letter->status != STATUS_DELIVERED) return 0;
    
    for (size_t i = 0; i < system->letters_count; i++) {
        if (system->letters[i].id == letter_id) {
            free(system->letters[i].technical_data);
            
            for (size_t j = i; j < system->letters_count - 1; j++) {
                system->letters[j] = system->letters[j + 1];
            }
            system->letters_count--;
            
            char log_msg[256];
            snprintf(log_msg, sizeof(log_msg), "Письмо %d забрано", letter_id);
            log_event(system, log_msg);
            
            return 1;
        }
    }
    
    return 0;
}

void process_letters(MailSystem *system) {
    if (!system) return;
 
    for (size_t i = 0; i < system->offices_count; i++) {
        MailOffice *office = &system->offices[i];
        
        if (!is_empty_heap(&office->letter_heap)) {
            int priority = pop_heap(&office->letter_heap);
            office->current_count--;
            
            for (size_t j = 0; j < system->letters_count; j++) {
                Letter *letter = &system->letters[j];
                if (letter->current_office_id == office->id && 
                    -letter->priority == priority &&
                    letter->status == STATUS_IN_TRANSIT) {
                    
                    if (letter->to_office_id == office->id) {
                        letter->status = STATUS_DELIVERED;
                        printf(">>> Письмо %d ДОСТАВЛЕНО в отделение %d!\n", letter->id, office->id);
                        char log_msg[256];
                        snprintf(log_msg, sizeof(log_msg), 
                                 "Письмо %d доставлено в отделение %d", letter->id, office->id);
                        log_event(system, log_msg);
                    } else {
                        MailOffice *next_office = NULL;
                        MailOffice *best_office = NULL;
                        
                        for (size_t k = 0; k < office->connected_count; k++) {
                            MailOffice *candidate = find_office(system, office->connected_offices[k]);
                            if (candidate && candidate->id == letter->to_office_id && 
                                candidate->current_count < candidate->capacity) {
                                best_office = candidate;
                                break;
                            }
                        }
                        
                        if (!best_office) {
                            for (size_t k = 0; k < office->connected_count; k++) {
                                MailOffice *candidate = find_office(system, office->connected_offices[k]);
                                if (candidate && candidate->current_count < candidate->capacity) {
                                    if (is_office_connected(candidate, letter->to_office_id)) {
                                        best_office = candidate;
                                        break;
                                    }
                                    if (!next_office) {
                                        next_office = candidate;
                                    }
                                }
                            }
                        }
                        
                        MailOffice *target_office = best_office ? best_office : next_office;
                        
                        if (target_office) {
                            letter->current_office_id = target_office->id;
                            push_heap(&target_office->letter_heap, -letter->priority);
                            target_office->current_count++;
                            
                            printf("Письмо %d переслано из %d в %d (цель: %d)\n", 
                                   letter->id, office->id, target_office->id, letter->to_office_id);
                            
                            char log_msg[256];
                            snprintf(log_msg, sizeof(log_msg), 
                                     "Письмо %d переслано из отделения %d в отделение %d", 
                                     letter->id, office->id, target_office->id);
                            log_event(system, log_msg);
                        } else {
                            letter->status = STATUS_UNDELIVERED;
                            printf("Письмо %d НЕ ДОСТАВЛЕНО - нет доступного маршрута из %d в %d\n", 
                                   letter->id, office->id, letter->to_office_id);
                            char log_msg[256];
                            snprintf(log_msg, sizeof(log_msg), 
                                     "Письмо %d помечено как недоставленное - нет маршрута из %d в %d", 
                                     letter->id, office->id, letter->to_office_id);
                            log_event(system, log_msg);
                        }
                    }
                    break;
                }
            }
        }
    }
}

void save_letters_to_file(const MailSystem *system, const char *filename) {
    if (!system || !filename) return;
    
    FILE *file = fopen(filename, "w");
    if (!file) return;
    
    fprintf(file, "ID, Тип, Статус, Приоритет, Откуда, Куда, ТекущееОтделение, ТехническиеДанные\n");
    
    for (size_t i = 0; i < system->letters_count; i++) {
        const Letter *letter = &system->letters[i];
        
        const char *type_str = (letter->type == LETTER_REGULAR) ? "ОБЫЧНОЕ" : "СРОЧНОЕ";
        const char *status_str;
        switch (letter->status) {
            case STATUS_IN_TRANSIT: 
                status_str = "В_ПУТИ";
                break;
            case STATUS_DELIVERED:
                status_str = "ДОСТАВЛЕНО";
                break;
            case STATUS_UNDELIVERED:
                status_str = "НЕ_ДОСТАВЛЕНО";
                break;
            default:
                status_str = "НЕИЗВЕСТНО";
        }
        
        fprintf(file, "%d, %s, %s, %d, %d, %d, %d, %s\n",
                letter->id, type_str, status_str, letter->priority,
                letter->from_office_id, letter->to_office_id,
                letter->current_office_id, letter->technical_data);
    }
    
    fclose(file);
}

void log_event(MailSystem *system, const char *event) {
    if (!system || !event || !system->log_filename) return;
    
    FILE *file = fopen(system->log_filename, "a");
    if (!file) return;
    
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    fprintf(file, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
            tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
            tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec,
            event);
    
    fclose(file);
}