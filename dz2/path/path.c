#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
print_matrix(unsigned long **table, int m, int n) {
    int i, j;
    n = n + 2;

    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            printf("%3lu ", table[i][j]);
        }
        printf("\n");
    }
}

unsigned long
minimum(unsigned long a, unsigned long b) {
    if(a < b)
        return a;
    else
        return b;
}

unsigned long**
ex_allocate(int m, int n) {
    unsigned long **table;
    int i, nn = n + 2;

    table = malloc(m * sizeof(long *));

    for(i = 0; i < m; i++) {
        table[i] = malloc(nn * sizeof(long));
        memset(table[i], -1, nn * sizeof(long));
    }

    return table;
}

void
ex_deallocate(unsigned long **table, int m, int n) {
    int i, nn = n+ 2;

    for(i = 0; i < m; i++)
        free(table[i]);

    free(table);
}


int
main(void) {
    /* costs - the input matrix
     * weighted - the calculated weight matrix
     * entry - the matrix containing entry columns
     * L - left pass array; R - right pass array
     * LC - left pass columns; RC - right pass columns
     * S - stack vector */
    unsigned long **costs, **weighted, **entry;
    unsigned long *L, *R, *LC, *RC, *S;
    int m, n;

    /* utility variables:
     * i, j - counters
     * rj - reverse utility counter used fro right side approach
     * sp - stack pointer for output reconstruction
     * left - stores previous left cost during the iteration
     * right - stores previous right cost during the iteration
     * lunder - stores left pass value underneath current iterator position
     * runder - stores right pass value underneath current iterator position
     * weight - holds current weight during reconstruction
     * cursor - current column of descent used during reconstruction */
    int i, j, rj, sp = 0;
    unsigned long left, right, lunder, runder, weight = -1, cursor = 1;

    scanf("%d%d", &m, &n);

    costs = ex_allocate(m, n);
    weighted = ex_allocate(m, n);
    entry = ex_allocate(m, n);

    L = malloc((n + 2) * sizeof(long));
    LC = malloc((n + 2) * sizeof(long));
    memset(L, -1, (n + 2) * sizeof(long));

    R = malloc((n + 2) * sizeof(long));
    RC = malloc((n + 2) * sizeof(long));
    memset(R, -1, (n + 2) * sizeof(long));

    S = malloc(n * m * sizeof(int));

    for(i = 0; i < m; i++)
        for(j = 1; j < n + 1; j++) {
            scanf("%lu", &costs[i][j]);
            weighted[i][j] = costs[i][j];
        }

    /*print_matrix(costs, m, n);*/

    /* algorithm */
    for(i = 1; i < m; i++) {
        for(j = 1; j < n + 1; j++) {
            rj = n + 1 - j;     // calculate the right pass index

            left = L[j - 1];    // calculate the left pass cost
            right = R[rj + 1];  // calculate the right pass cost
            lunder = weighted[i - 1][j];   // calculate the left index upward cost
            runder = weighted[i - 1][rj];  // calculate the right index upward cost

            L[j] = minimum(left, lunder) + costs[i][j];     // choose the cheaper left pass cost
            R[rj] = minimum(right, runder) + costs[i][rj];  // choose the cheaper right pass cost

            /*printf("currentL: %lu; currentR: %lu\n", weighted[i][j], weighted[i][rj]);*/
            /*printf("left: %lu; lunder %lu; right: %lu; runder: %lu\n", left, lunder, right, runder);*/
            /*printf("L: %lu; R: %lu\n", L[j], R[rj]);*/

            LC[j] = (L[j] == left + costs[i][j] ? LC[j - 1] : j);
            RC[rj] = (R[rj] == right + costs[i][rj] ? RC[rj + 1] : rj);

            /*printf("%lu ", R[j]);*/
        }

        for(j = 1; j < n + 1; j++) {
            weighted[i][j] = minimum(L[j], R[j]);
            entry[i][j] = (weighted[i][j] == L[j] ? LC[j] : RC[j]);
        }
    }

    for(j = 1; j < n + 1; j++) {
        if(weight > weighted[m - 1][j]) {
            weight = weighted[m - 1][j];
            cursor = j;
        }
    }

    j = cursor;
    for(i = m - 1; i >= 0; i--) {
        while(j != cursor) {
            S[sp] = j;
            sp++;
            j < cursor ? j++ : j--;
        }
        S[sp] = j;
        sp++;
        if(i - 1 > 0) {
            cursor = entry[i - 1][cursor];
        }
    }

    while(sp-- != 0) {
        printf("%d ", S[sp]);
    }

    ex_deallocate(costs, m, n);
    ex_deallocate(weighted, m, n);
    ex_deallocate(entry, m, n);

    free(L);
    free(R);
    free(LC);
    free(RC);
    free(S);

    return 0;
}