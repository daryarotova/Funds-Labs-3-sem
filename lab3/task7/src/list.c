#include "../include/list.h"
#include <stdlib.h>

TokenList list_create() {
    TokenList list = {NULL, NULL, 0};
    return list;
}

void list_push_back(TokenList* list, TokenItem value) {
    ListNode* node = malloc(sizeof(ListNode));
    if (!node) return;
    
    node->item = value;
    node->next = NULL;
    node->prev = list->tail;
    
    if (list->tail) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
    list->size++;
}

void list_push_front(TokenList* list, TokenItem value) {
    ListNode* node = malloc(sizeof(ListNode));
    if (!node) return;
    
    node->item = value;
    node->prev = NULL;
    node->next = list->head;
    
    if (list->head) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }
    list->head = node;
    list->size++;
}

void list_pop_back(TokenList* list) {
    if (!list->tail) return;
    
    ListNode* to_remove = list->tail;
    list->tail = to_remove->prev;
    
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    
    free(to_remove);
    list->size--;
}

void list_pop_front(TokenList* list) {
    if (!list->head) return;
    
    ListNode* to_remove = list->head;
    list->head = to_remove->next;
    
    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    
    free(to_remove);
    list->size--;
}

TokenItem list_peek_front(const TokenList* list) {
    static TokenItem empty = {TOKEN_NONE, {0}};
    if (list->head != NULL) {
        return list->head->item;
    } else {
        return empty;
    }
}

TokenItem list_peek_back(const TokenList* list) {
    static TokenItem empty = {TOKEN_NONE, {0}};
    if (list->tail != NULL) {
        return list->tail->item;
    } else {
        return empty;
    }
}

void list_clear(TokenList* list) {
    while (list->head) {
        list_pop_front(list);
    }
}

void stack_push(TokenList* stack, TokenItem value) {
    list_push_front(stack, value);
}

TokenItem stack_pop(TokenList* stack) {
    TokenItem item = list_peek_front(stack);
    if (stack->head) {
        list_pop_front(stack);
    }
    return item;
}

TokenItem stack_top(const TokenList* stack) {
    return list_peek_front(stack);
}

void queue_enqueue(TokenList* queue, TokenItem value) {
    list_push_back(queue, value);
}

TokenItem queue_dequeue(TokenList* queue) {
    TokenItem item = list_peek_front(queue);
    if (queue->head) {
        list_pop_front(queue);
    }
    return item;
}

TokenItem queue_peek(const TokenList* queue) {
    return list_peek_front(queue);
}
