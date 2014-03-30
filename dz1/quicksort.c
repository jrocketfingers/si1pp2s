#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "quicksort.h"

void swap(void *a, void *b, size_t size)
{
    void *t;
    t = malloc(size);
    memcpy(t, a, size);
    memcpy(a, b, size);
    memcpy(b, t, size);

    free(t);
}

int partition(void *A, int left, int right, size_t size, int (*compare)(void *a, void *b))
{
    int i, j;
    void *pivot = (char *)A + right * size;
    i = left - 1;

    for(j = left; j < right; j++)
    {
        if(compare((char *)A + j * size, pivot))
        {
            i++;
            swap((char *)A + j * size, (char *)A + i * size, size);
        }
    }
    swap((char *)A + (i+1) * size, (char *)A + right * size, size);
    return i + 1;
}

void quickloop(void *A, int left, int right, size_t size, int (*compare)(void *a, void *b))
{
    if(left < right)
    {
        int pivot = partition(A, left, right, size, compare);
        quickloop(A, left, pivot - 1, size, compare);
        quickloop(A, pivot + 1, right, size, compare);
    }
}

void quicksort(void *A, int n, size_t size, int (*compare)(void *a, void *b))
{
    quickloop(A, 0, n - 1, size, compare);
}