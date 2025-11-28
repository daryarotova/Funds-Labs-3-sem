#include "../include/linked_list.h"
#include <stdlib.h>
#include <stdio.h>

LinkedList create_list(void) {
    LinkedList list;
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
    return list;
}

void erase_list(LinkedList* list) {
    if (!list) return;
    
    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        liver_free(current->data);
        free(current);
        current = next;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void delete_list(LinkedList* list) {
    if (!list) return;
    erase_list(list);
}

void push_back_list(LinkedList* list, Liver* value) {
    if (!list || !value) return;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = list->tail;
    
    if (list->tail) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    
    list->tail = new_node;
    list->size++;
}

void push_front_list(LinkedList* list, Liver* value) {
    if (!list || !value) return;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = list->head;
    
    if (list->head) {
        list->head->prev = new_node;
    } else {
        list->tail = new_node;
    }
    
    list->head = new_node;
    list->size++;
}

Liver* pop_back_list(LinkedList* list) {
    if (!list || !list->tail) return NULL;
    
    Node* last_node = list->tail;
    Liver* data = last_node->data;
    
    list->tail = last_node->prev;
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    
    free(last_node);
    list->size--;
    
    return data;
}

Liver* pop_front_list(LinkedList* list) {
    if (!list || !list->head) return NULL;
    
    Node* first_node = list->head;
    Liver* data = first_node->data;
    
    list->head = first_node->next;
    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    
    free(first_node);
    list->size--;
    
    return data;
}

void insert_at_list(LinkedList* list, size_t index, Liver* value) {
    if (!list || !value || index > list->size) return;
    
    if (index == 0) {
        push_front_list(list, value);
        return;
    }
    
    if (index == list->size) {
        push_back_list(list, value);
        return;
    }
    
    Node* current = list->head;
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    
    new_node->data = value;
    new_node->prev = current;
    new_node->next = current->next;
    
    current->next->prev = new_node;
    current->next = new_node;
    
    list->size++;
}

void delete_at_list(LinkedList* list, size_t index) {
    if (!list || index >= list->size) return;
    
    if (index == 0) {
        Liver* data = pop_front_list(list);
        if (data) liver_free(data);
        return;
    }
    
    if (index == list->size - 1) {
        Liver* data = pop_back_list(list);
        if (data) liver_free(data);
        return;
    }
    
    Node* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    current->prev->next = current->next;
    current->next->prev = current->prev;
    
    liver_free(current->data);
    free(current);
    list->size--;
}

Liver* get_at_list(const LinkedList* list, size_t index) {
    if (!list || index >= list->size) return NULL;
    
    Node* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

int is_equal_list(const LinkedList* l1, const LinkedList* l2) {
    if (!l1 || !l2) return 0;
    if (l1->size != l2->size) return 0;
    
    Node* node1 = l1->head;
    Node* node2 = l2->head;
    
    while (node1 && node2) {
        if (node1->data->id != node2->data->id) {
            return 0;
        }
        node1 = node1->next;
        node2 = node2->next;
    }
    
    return 1;
}

void push_stack(LinkedList* stack, Liver* value) {
    push_back_list(stack, value);
}

Liver* pop_stack(LinkedList* stack) {
    return pop_back_list(stack);
}

Liver* peek_stack(const LinkedList* stack) {
    if (!stack || !stack->tail) return NULL;
    return stack->tail->data;
}

void enqueue(LinkedList* queue, Liver* value) {
    push_back_list(queue, value);
}

Liver* dequeue(LinkedList* queue) {
    return pop_front_list(queue);
}

Liver* peek_queue(const LinkedList* queue) {
    if (!queue || !queue->head) return NULL;
    return queue->head->data;
}