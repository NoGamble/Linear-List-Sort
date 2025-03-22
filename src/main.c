#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sorting.h"
#include "../include/storage.h"
#include "../include/input_handler.h"
#include "../include/output_handler.h"

void print_usage() {
    printf("Usage: sorting_tool [OPTIONS]\n\n");
    printf("Options:\n");
    printf("  --file <filename>          Read numbers from a text file (one number per line)\n");
    printf("  --csv <filename>           Read numbers from a CSV file (comma-separated)\n");
    printf("  --stdin                    Read numbers from standard input (supports pipeline)\n");
    printf("  --output <filename>        Write sorted numbers to a file instead of stdout\n");
    printf("  --storage <type>           Choose storage type: array or linked (default: array)\n");
    printf("  --sort-method <method>     Choose sorting algorithm: bubble, quick (default: quick)\n");
    printf("  --help                     Show this help message and exit\n\n");
    printf("Examples:\n");
    printf("  sorting_tool --file input.txt --sort-method=bubble\n");
    printf("  sorting_tool --csv data.csv --output sorted.txt --storage=linked\n");
    printf("  cat numbers.txt | sorting_tool --stdin --sort-method=quick\n");
}

int main(int argc, char *argv[]) {
    char *input_file = NULL, *output_file = NULL;
    StorageType storage_type = ARRAY_STORAGE;
    SortMethod sort_method = QUICK_SORT;
    int use_stdin = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_usage();
            return 0;
        } else if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            input_file = argv[++i];
        } else if (strcmp(argv[i], "--csv") == 0 && i + 1 < argc) {
            input_file = argv[++i];
        } else if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "--storage") == 0 && i + 1 < argc) {
            if (strcmp(argv[i + 1], "array") == 0) {
                storage_type = ARRAY_STORAGE;
            } else if (strcmp(argv[i + 1], "linked") == 0) {
                storage_type = LINKED_STORAGE;
            } else {
                fprintf(stderr, "Error: Unknown storage type '%s'\n", argv[i + 1]);
                print_usage();
                return 1;
            }
            i++;
        } else if (strcmp(argv[i], "--sort-method") == 0 && i + 1 < argc) {
            if (strcmp(argv[i + 1], "bubble") == 0) {
                sort_method = BUBBLE_SORT;
            } else if (strcmp(argv[i + 1], "quick") == 0) {
                sort_method = QUICK_SORT;
            } else {
                fprintf(stderr, "Error: Unknown sorting method '%s'\n", argv[i + 1]);
                print_usage();
                return 1;
            }
            i++;
        } else if (strcmp(argv[i], "--stdin") == 0) {
            use_stdin = 1;
        } else {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
            print_usage();
            return 1;
        }
    }

    if (!input_file && !use_stdin) {
        fprintf(stderr, "Error: No input source specified.\n");
        print_usage();
        return 1;
    }

    //create linear list
    LIST *list = create_list(storage_type);
    if (!list) {
        fprintf(stderr, "Error: Failed to create list.\n");
        return 1;
    }

    // input
    if (use_stdin) {
        read_from_stdin(list);
    } else if (input_file) {
        read_from_file(list, input_file);
    }

    // sort
    int size = list_length(list);
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) arr[i] = list_get(list, i);
    if (sort_method == BUBBLE_SORT) {
        bubble_sort(arr, size);
    } else if (sort_method == QUICK_SORT) {
        quick_sort(arr, 0, size - 1);
    }
    for (int i = 0; i < size; i++) list_insert(list, i, arr[i]);
    free(arr);

    // output
    if (output_file) {
        write_to_file(list, output_file);
    } else {
        print_list(list);
    }

    destroy_list(list);
    return 0;
}
