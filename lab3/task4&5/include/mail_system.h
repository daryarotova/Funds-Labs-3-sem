#ifndef MAIL_SYSTEM_H
#define MAIL_SYSTEM_H

#include "heap.h"
#include <time.h>

typedef enum {
    LETTER_REGULAR,
    LETTER_URGENT
} LetterType;

typedef enum {
    STATUS_IN_TRANSIT,
    STATUS_DELIVERED,
    STATUS_UNDELIVERED
} LetterStatus;

typedef struct Letter {
    int id;
    LetterType type;
    LetterStatus status;
    int priority;
    int from_office_id;
    int to_office_id;
    char *technical_data;
    int current_office_id;
} Letter;

typedef struct MailOffice {
    int id;
    int capacity;
    int current_count;
    Heap letter_heap;
    int *connected_offices;
    size_t connected_count;
} MailOffice;

typedef struct MailSystem {
    MailOffice *offices;
    size_t offices_count;
    size_t offices_capacity;
    Letter *letters;
    size_t letters_count;
    size_t letters_capacity;
    int next_letter_id;
    char *log_filename;
} MailSystem;

MailSystem create_mail_system();
void delete_mail_system(MailSystem *system);
int add_mail_office(MailSystem *system, int id, int capacity, const int *connected_offices, size_t connected_count);
int remove_mail_office(MailSystem *system, int office_id);
int add_letter(MailSystem *system, LetterType type, int priority, int from_office, int to_office, const char *tech_data);
int mark_letter_undelivered(MailSystem *system, int letter_id);
int pickup_letter(MailSystem *system, int letter_id);
void process_letters(MailSystem *system);
void save_letters_to_file(const MailSystem *system, const char *filename);
void log_event(MailSystem *system, const char *event);

MailOffice* find_office(MailSystem *system, int office_id);
Letter* find_letter(MailSystem *system, int letter_id);
int is_office_connected(const MailOffice *office, int target_office_id);

#endif