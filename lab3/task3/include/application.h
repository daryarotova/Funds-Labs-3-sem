#ifndef APPLICATION_H
#define APPLICATION_H

#include "linked_list.h"
#include "undo.h"
#include "search.h"

typedef struct {
    LinkedList livers;
    UndoManager undo_manager;
} AppState;

void app_init(AppState* state);
void app_cleanup(AppState* state);

void app_load_file(AppState* state);
void app_save_file(AppState* state);
void app_add_liver(AppState* state);
void app_edit_liver(AppState* state);
void app_delete_liver(AppState* state);
void app_search_liver(AppState* state);
void app_undo(AppState* state);
void app_print_all(AppState* state);

#endif