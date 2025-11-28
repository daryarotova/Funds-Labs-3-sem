#ifndef INTERFACE_H
#define INTERFACE_H

#include "mail_system.h"
#include <signal.h>

extern volatile sig_atomic_t auto_process;
void handle_signal(int sig);
void sleep_ms(int milliseconds);

void print_offices_info(MailSystem *system);
void print_letters_status(MailSystem *system);
void print_menu();

void load_mappings(MailSystem *system, const char *filename);
void auto_process_letters(MailSystem *system);

#endif