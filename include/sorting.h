#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED

typedef enum { BUBBLE_SORT, QUICK_SORT } SortMethod;

void bubble_sort(int arr[], int size);
void quick_sort(int arr[], int left, int right);

#endif // SORTING_H_INCLUDED
