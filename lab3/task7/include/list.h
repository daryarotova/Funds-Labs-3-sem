#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include "tokens.h"

typedef struct ListNode {
    TokenItem item;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

typedef struct {
    ListNode* head;
    ListNode* tail;
    size_t size;
} TokenList;

TokenList list_create();
void list_push_back(TokenList* list, TokenItem value);
void list_push_front(TokenList* list, TokenItem value);
void list_pop_back(TokenList* list);
void list_pop_front(TokenList* list);
TokenItem list_peek_front(const TokenList* list);
TokenItem list_peek_back(const TokenList* list);
void list_clear(TokenList* list);

void stack_push(TokenList* stack, TokenItem value);
TokenItem stack_pop(TokenList* stack);
TokenItem stack_top(const TokenList* stack);

void queue_enqueue(TokenList* queue, TokenItem value);
TokenItem queue_dequeue(TokenList* queue);
TokenItem queue_peek(const TokenList* queue);

#endif
