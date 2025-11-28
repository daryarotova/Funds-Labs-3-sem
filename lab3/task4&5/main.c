#include "include/mail_system.h"
#include "include/interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <файл_маппингов> [лог_файл]\n", argv[0]);
        return 1;
    }
    
    signal(SIGINT, handle_signal);
    
    MailSystem system = create_mail_system();
    
    if (argc >= 3) {
        system.log_filename = malloc(strlen(argv[2]) + 1);
        strcpy(system.log_filename, argv[2]);
    } else {
        system.log_filename = malloc(strlen("mail_system.log") + 1);
        strcpy(system.log_filename, "mail_system.log");
    }
    
    load_mappings(&system, argv[1]);
    print_offices_info(&system); 
    
    int running = 1;
    
    while (running) {
        print_menu();
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Неверный ввод!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1: {
                int id, capacity;
                printf("Введите ID отделения: ");
                scanf("%d", &id);
                printf("Введите вместимость: ");
                scanf("%d", &capacity);
                
                printf("Введите количество связанных отделений: ");
                size_t connected_count;
                scanf("%zu", &connected_count);
                
                int *connected = malloc(connected_count * sizeof(int));
                printf("Введите ID связанных отделений: ");
                for (size_t i = 0; i < connected_count; i++) {
                    scanf("%d", &connected[i]);
                }
                
                if (add_mail_office(&system, id, capacity, connected, connected_count)) {
                    printf("Почтовое отделение %d добавлено!\n", id);
                } else {
                    printf("Ошибка добавления отделения!\n");
                }
                free(connected);
                break;
            }
            
            case 2: {
                int office_id;
                printf("Введите ID отделения для удаления: ");
                scanf("%d", &office_id);
                
                if (remove_mail_office(&system, office_id)) {
                    printf("Почтовое отделение %d удалено!\n", office_id);
                } else {
                    printf("Ошибка удаления отделения!\n");
                }
                break;
            }
            
            case 3: {
                int type, priority, from_office, to_office;
                char tech_data[256];
                
                printf("Тип письма (0-Обычное, 1-Срочное): ");
                scanf("%d", &type);
                printf("Приоритет: ");
                scanf("%d", &priority);
                printf("ID отделения отправителя: ");
                scanf("%d", &from_office);
                printf("ID отделения получателя: ");
                scanf("%d", &to_office);
                printf("Технические данные: ");
                scanf("%255s", tech_data);
                
                int letter_id = add_letter(&system, (LetterType)type, priority, from_office, to_office, tech_data);
                if (letter_id > 0) {
                    printf("Письмо добавлено с ID: %d\n", letter_id);
                } else {
                    printf("Ошибка добавления письма!\n");
                }
                break;
            }
            
            case 4: {
                int letter_id;
                printf("Введите ID письма: ");
                scanf("%d", &letter_id);
                
                if (mark_letter_undelivered(&system, letter_id)) {
                    printf("Письмо %d помечено как недоставленное!\n", letter_id);
                } else {
                    printf("Ошибка пометки письма!\n");
                }
                break;
            }
            
            case 5: {
                int letter_id;
                printf("Введите ID письма: ");
                scanf("%d", &letter_id);
                
                if (pickup_letter(&system, letter_id)) {
                    printf("Письмо %d забрано!\n", letter_id);
                } else {
                    printf("Ошибка забора письма!\n");
                }
                break;
            }
            
            case 6: {
                char filename[256];
                printf("Введите имя файла для сохранения: ");
                scanf("%255s", filename);
                save_letters_to_file(&system, filename);
                printf("Список писем сохранен в %s\n", filename);
                break;
            }
            
            case 7: {
                auto_process = 1;
                auto_process_letters(&system);
                break;
            }

            case 8:
                print_offices_info(&system);
                break;
            
            case 9:
                print_letters_status(&system);
                break;
            
            case 10:
                running = 0;
                printf("Выход из программы. До свидания!\n");
                break;
                
            default:
                printf("Неверный выбор. Попробуйте снова!\n");
                break;
        }
    }
    
    delete_mail_system(&system);
    return 0;
}
