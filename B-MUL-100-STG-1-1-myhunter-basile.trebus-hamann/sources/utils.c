/*
** EPITECH PROJECT, 2021
** utils.c
** File description:
** lib
*/

#include "../includes/my_hunter.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    int i;

    i = 0;
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i = i + 1;
    }
    write (1, "\n", 2);
}

int my_strlen(char const *str)
{
    int i;

    i = 0;
    while (str[i] != '\0') {
        i = i + 1;
    }
    return (i);
}

char *my_revstr(char *str)
{
    int i;
    int l;
    char x;

    i = 0;
    l = my_strlen(str) - 1;
    while (i < l) {
        x = str[i];
        str[i] = str[l];
        str[l] = x;
        i = i + 1;
        l = l - 1;
    }
    return (str);
}

int get_int_len(int nb)
{
    int res = 0;
    int tmp = nb;
    if (nb <= 0)
        return (1);
    while (tmp > 0) {
        tmp = tmp / 10;
        res++;
    }
    return (res);
}