#include "../include/storage.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int length;
} LinkedList;

LIST* create_list(StorageType type) {
    if (type != LINKED_STORAGE) return NULL;
    LinkedList *list = (LinkedList*) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->length = 0;
    return (LIST*) list;
}

void destroy_list(LIST* list) {
    Node *current = ((LinkedList*) list)->head;
    while (current) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int list_length(LIST *list) {
    return ((LinkedList*) list)->length;
}

int list_get(LIST *list, int pos) {
    LinkedList *l = (LinkedList*) list;
    if (pos < 0 || pos >= l->length) return -1;
    Node *cur = l->head;
    for (int i = 0; i < pos; i++) cur = cur->next;
    return cur->value;
}

int list_insert(LIST *list, int pos, int x) {
    LinkedList *l = (LinkedList*) list;
    if (pos < 0 || pos > l->length) return -1;

    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->value = x;

    if (pos == 0) {
        new_node->next = l->head;
        l->head = new_node;
    } else {
        Node *prev = l->head;
        for (int i = 0; i < pos - 1; i++) prev = prev->next;
        new_node->next = prev->next;
        prev->next = new_node;
    }

    l->length++;
    return 0;
}

int list_delete(LIST *list, int pos) {
    LinkedList *l = (LinkedList*) list;
    if (pos < 0 || pos >= l->length) return -1;

    Node *to_delete;
    if (pos == 0) {
        to_delete = l->head;
        l->head = l->head->next;
    } else {
        Node *prev = l->head;
        for (int i = 0; i < pos - 1; i++) prev = prev->next;
        to_delete = prev->next;
        prev->next = to_delete->next;
    }

    free(to_delete);
    l->length--;
    return 0;
}
