/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** random.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

int random_number(int min_num, int max_num)
{
    int result = 0;
    int low_num = 0;
    int hi_num = 0;

    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1;
    } else {
        low_num = max_num + 1;
        hi_num = min_num;
    }
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

float random_float(float scale)
{
    float n;

    n = ((float)rand()/RAND_MAX)*(float)(scale);
    return n;
}

int random_between(int lower, int upper)
{
    int num = 0;

    for (int i = 0; i < 10; i++)
        num = (rand() % (upper - lower + 1)) + lower;
    return num;
}
