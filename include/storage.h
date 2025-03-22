#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED

typedef enum { ARRAY_STORAGE, LINKED_STORAGE } StorageType;

struct list_t;
typedef struct list_t LIST;

LIST* create_list(StorageType type);

void destroy_list(LIST* list);

int list_length(LIST *list);

int list_get(LIST *list, int pos);

int list_insert(LIST *list, int pos, int x);

int list_delete(LIST *list, int pos);

#endif 
