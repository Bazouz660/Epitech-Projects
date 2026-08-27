/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** utils2.c
*/

#include "../includes/my_runner.h"

float random_number(int min_num, int max_num)
{
    int result = 0;
    int low_num = 0;
    int hi_num = 0;
    float res = 0;

    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1;
    } else {
        low_num = max_num + 1;
        hi_num = min_num;
    }
    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    res = (float)result / 10;
    return res;
}

int	my_atoi(char *str)
{
    int res = 0;
    int sign = 0;
    int i = 0;

    (str[i] == '-' ? sign = 1, i++ : 0);
    for (; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9')
	        res = (res * 10) + str[i] - '0';
        else
	        return (res);
    }
    if (sign == 0)
        return (res);
    else
        return (-res);
}

int get_int_len(int nb)
{
    int len = 0;

    while (nb > 0) {
        nb = nb/10;
        len++;
    }
    return (len + 1);
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i = i + 1;
    if (s1[i] < s2[i] || s1[i] == '\0' && s1[i] != s2[i])
        return (-1);
    else if (s1[i] > s2[i] || s2[i] == '\0' && s1[i] != s2[i])
        return (1);
    else
        return (0);
}
