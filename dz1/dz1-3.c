#include <stdio.h>
#include <string.h>

int main(void)
{
    int types[26];
    int K, N, i, total = 0;
    char type;

    memset(types, 0, sizeof(int) * 26);

    scanf("%d%d", &K, &N);

    while(getchar() != '\n');
    for(i = 0; i < N; i++)
    {
        scanf("%c", &type);
        types[type - 'A']++;
    }

    for(i = 0; i < 26; i++)
        total += types[i] / K + (types[i] % K > 0);

    printf("%d", total);

    return 0;
}
