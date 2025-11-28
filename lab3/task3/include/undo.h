#ifndef UNDO_H
#define UNDO_H

#include "linked_list.h"

typedef enum {
    ACTION_ADD,
    ACTION_DELETE,
    ACTION_MODIFY
} ActionType;

typedef struct {
    ActionType type;
    Liver* liver_state;
    size_t index;
} UndoAction;

typedef struct {
    LinkedList actions_stack;
    size_t modification_count;
} UndoManager;

void undo_init(UndoManager* manager);
void undo_clear(UndoManager* manager);

void undo_register_add(UndoManager* manager, Liver* liver, size_t index);
void undo_register_delete(UndoManager* manager, Liver* liver, size_t index);
void undo_register_modify(UndoManager* manager, Liver* old_liver, size_t index);

void undo_last_half(UndoManager* manager, LinkedList* main_list);

#endif