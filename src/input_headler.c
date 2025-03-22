#include "../include/input_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* from txt */
int read_from_file(LIST *list, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return -1;
    }

    int num, index = 0;
    while (fscanf(file, "%d", &num) == 1) {
        list_insert(list, index++, num);
    }

    fclose(file);
    return 0;
}

/* from CSV */
int read_from_csv(LIST *list, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return -1;
    }

    char buffer[1024];
    int index = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        char *token = strtok(buffer, ",");
        while (token) {
            int num = atoi(token);
            list_insert(list, index++, num);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
    return 0;
}

/* from stdin */
int read_from_stdin(LIST *list) {
    int num, index = 0;
    printf("Enter numbers (Ctrl+D to finish):\n");

    while (scanf("%d", &num) == 1) {
        list_insert(list, index++, num);
    }

    return 0;
}
