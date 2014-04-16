#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a >= b ? a : b;
}

int main(void) {
    int neighbors[101], sum[101], output[50], n, i, pera, sp = 0;

    scanf("%d", &n);

    for(i = 0; i < n; i++)
        scanf("%d", &neighbors[i]);

    sum[0] = neighbors[0];
    sum[1] = neighbors[1];
    neighbors[n] = neighbors[0];

    for(i = 2; i < n + 1; i++)
        sum[i] = max(sum[i - 2] + neighbors[i], sum[i - 1]);

    i--;

    printf("%d\n", sum[n] - neighbors[n]);

    while(i >= 2)
        if(sum[i] - neighbors[i] == sum[i - 2]) {
            /* magic */
            pera = i - 2;
            while(sum[i] - neighbors[i] == sum[pera]) pera--;
            i = pera + 1;
            output[sp++] = i;
            /* endmagic */
        } else
            i--;

    while(sp-- > 0)
        printf("%d ", output[sp] + 1);

    return 0;
}