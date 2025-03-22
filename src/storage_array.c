#include "../include/storage.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct {
    int data[MAX_SIZE];
    int length;
} ArrayList;

LIST* create_list(StorageType type) {
    if (type != ARRAY_STORAGE) return NULL;
    ArrayList *list = (ArrayList*) malloc(sizeof(ArrayList));
    list->length = 0;
    return (LIST*) list;
}

void destroy_list(LIST* list) {
    free(list);
}

int list_length(LIST *list) {
    return ((ArrayList*) list)->length;
}

int list_get(LIST *list, int pos) {
    ArrayList *arr = (ArrayList*) list;
    if (pos < 0 || pos >= arr->length) return -1;
    return arr->data[pos];
}

int list_insert(LIST *list, int pos, int x) {
    ArrayList *arr = (ArrayList*) list;
    if (pos < 0 || pos > arr->length || arr->length >= MAX_SIZE) return -1;
    for (int i = arr->length; i > pos; i--) arr->data[i] = arr->data[i - 1];
    arr->data[pos] = x;
    arr->length++;
    return 0;
}

int list_delete(LIST *list, int pos) {
    ArrayList *arr = (ArrayList*) list;
    if (pos < 0 || pos >= arr->length) return -1;
    for (int i = pos; i < arr->length - 1; i++) arr->data[i] = arr->data[i + 1];
    arr->length--;
    return 0;
}
