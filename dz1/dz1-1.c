#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "quicksort.h"

int odd_number_cond(int number)
{
    if(number % 2 == 0)
        printf("You must enter an odd number!\n");

    return number % 2;
}

int compare(void *a, void *b)
{
    return *(int*)a < *(int*)b;
}

int main(void)
{
    int K, *V, i, min = 0;

    printf("Broj glasackih jedinica: ");
    K = readint(odd_number_cond);

    V = calloc(K, sizeof(int));

    for(i = 0; i < K; i++)
        V[i] = readint(odd_number_cond);

    quicksort(V, K, sizeof(int), compare);

    for(i = 0; i < K / 2 + 1; i++)
        min = min + V[i] / 2 + 1;

    printf("Minimum: %d\n", min);

    return 0;
}