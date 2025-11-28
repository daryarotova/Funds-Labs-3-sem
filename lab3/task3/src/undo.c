#include "../include/undo.h"
#include "../include/liver.h"
#include "../include/search.h" 
#include "../include/file_operations.h"
#include <stdlib.h>
#include <stdio.h>

void undo_init(UndoManager* manager) {
    if (!manager) return;
    
    manager->actions_stack = create_list();
    manager->modification_count = 0;
}

void undo_clear(UndoManager* manager) {
    if (!manager) return;
    
    while (manager->actions_stack.size > 0) {
        Liver* action_ptr = pop_stack(&manager->actions_stack);
        if (action_ptr) {
            UndoAction* action = (UndoAction*)action_ptr;
            if (action->liver_state) {
                liver_free(action->liver_state);
            }
            free(action);
        }
    }
    
    erase_list(&manager->actions_stack);
    manager->modification_count = 0;
}

void undo_register_add(UndoManager* manager, Liver* liver, size_t index) {
    if (!manager || !liver) return;
    
    UndoAction* action = (UndoAction*)malloc(sizeof(UndoAction));
    if (!action) return;
    
    action->type = ACTION_ADD;
    action->liver_state = liver_copy(liver);
    action->index = index;
    
    push_stack(&manager->actions_stack, (Liver*)action);
    manager->modification_count++;
}

void undo_register_delete(UndoManager* manager, Liver* liver, size_t index) {
    if (!manager || !liver) return;
    
    UndoAction* action = (UndoAction*)malloc(sizeof(UndoAction));
    if (!action) return;
    
    action->type = ACTION_DELETE;
    action->liver_state = liver_copy(liver);
    action->index = index;
    
    push_stack(&manager->actions_stack, (Liver*)action);
    manager->modification_count++;
}

void undo_register_modify(UndoManager* manager, Liver* old_liver, size_t index) {
    if (!manager || !old_liver) return;
    
    UndoAction* action = (UndoAction*)malloc(sizeof(UndoAction));
    if (!action) return;
    
    action->type = ACTION_MODIFY;
    action->liver_state = liver_copy(old_liver);
    action->index = index;
    
    push_stack(&manager->actions_stack, (Liver*)action);
    manager->modification_count++;
}

void undo_last_half(UndoManager* manager, LinkedList* main_list) {
    if (!manager || !main_list) return;
    
    size_t undo_count = manager->modification_count / 2;
    if (undo_count == 0) {
        printf("No modifications to undo\n");
        return;
    }
    
    printf("Undoing last %zu modifications...\n", undo_count);
    
    for (size_t i = 0; i < undo_count && manager->actions_stack.size > 0; i++) {
        Liver* action_ptr = pop_stack(&manager->actions_stack);
        if (!action_ptr) break;
        
        UndoAction* action = (UndoAction*)action_ptr;
        
        switch (action->type) {
            case ACTION_ADD:
                printf("Undo ADD: Removing liver ID %u\n", action->liver_state->id);
                Node* node_to_remove = search_by_id(main_list, action->liver_state->id);
                if (node_to_remove) {
                    size_t index = 0;
                    Node* current = main_list->head;
                    while (current && current != node_to_remove) {
                        current = current->next;
                        index++;
                    }
                    if (current) {
                        delete_at_list(main_list, index);
                    }
                }
                break;
                
            case ACTION_DELETE:
                printf("Undo DELETE: Restoring liver ID %u\n", action->liver_state->id);
                Liver* restored_liver = liver_copy(action->liver_state);
                if (restored_liver) {
                    insert_sorted_by_age(main_list, restored_liver);
                }
                break;
                            
            case ACTION_MODIFY:
                printf("Undo MODIFY: Restoring liver ID %u to previous state\n", action->liver_state->id);
                Node* node_to_modify = search_by_id(main_list, action->liver_state->id);
                if (node_to_modify) {
                    Liver* current_state = liver_copy(node_to_modify->data);
                    liver_free(node_to_modify->data);
                    node_to_modify->data = liver_copy(action->liver_state);
                    
                    liver_free(current_state);
                }
                break;
        }
        
        if (action->liver_state) {
            liver_free(action->liver_state);
        }
        free(action);
    }
    
    manager->modification_count -= undo_count;
    printf("Undo completed. Remaining modifications: %zu\n", manager->modification_count);
}