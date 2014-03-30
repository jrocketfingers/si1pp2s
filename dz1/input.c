#include <stdio.h>
#include "input.h"

int readint(int (*condition)(int))
{
    int value;
    scanf("%d", &value);
    if(condition)
    {
        while(!condition(value))
            scanf("%d", &value);
    }

    return value;
}

float readfloat(int (*condition)(float))
{
    float value;
    scanf("%f", &value);
    if(condition)
    {
        while(!condition(value))
            scanf("%d", &value);
    }

    return value;
}