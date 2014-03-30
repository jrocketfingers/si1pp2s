#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"

typedef struct farmer {
    int price;
    int amount;
} farmer_t;

int compare(void *a, void *b)
{
    return ((farmer_t *)a)->price < ((farmer_t *)b)->price;
}

int main(void)
{
    int i, target, n, total = 0;
    farmer_t *farmers;

    scanf("%d%d", &target, &n);

    farmers = calloc(n, sizeof(farmer_t));

    for(i = 0; i < n; i++)
    {
        scanf("%d%d", &(farmers[i].price), &(farmers[i].amount));
        /*printf("%d %d", &(farmers[i].price), &(farmers[i].amount));*/
    }

    quicksort(farmers, n, sizeof(farmer_t), compare);

    for(i = 0; i < n; i++)
    {
        if(farmers[i].amount > target)
        {
            total = total + target * farmers[i].price;
            break;
        }
        else
        {
            target = target - farmers[i].amount;
            total = total + farmers[i].amount * farmers[i].price;
        }
    }

    printf("%d\n", total);

    return 0;
}