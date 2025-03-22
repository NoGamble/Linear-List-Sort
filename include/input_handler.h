#ifndef INPUT_HANDLER_H_INCLUDED
#define INPUT_HANDLER_H_INCLUDED

#include "storage.h"

/* from txt */
int read_from_file(LIST *list, const char *filename);

/* from CSV */
int read_from_csv(LIST *list, const char *filename);

/* from  stdin */
int read_from_stdin(LIST *list);

#endif // INPUT_HANDLER_H_INCLUDED
