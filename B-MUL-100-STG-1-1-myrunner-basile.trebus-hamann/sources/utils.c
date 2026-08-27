/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** utils.c
*/

#include "../includes/my_runner.h"

int my_strlen(char const *str)
{
    int i;

    i = 0;
    while (str[i] != '\0') {
        i = i + 1;
    }
    return (i);
}

int random_int(int n)
{
    int r;
    r = rand();
    r = r % n;
    return r;
}

char *my_strcpy(char *dest, char const *src)
{
	int	i = 0;

	for (; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
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

char *int_to_string(char *str, int nb)
{
    int i = 0;
    int mem_nb = nb;
    int remains;

    if (nb == 0) {
        str[i] = '0';
        str[i + 1] = '\0';
        return (str);
    }
    (nb < 0) ? nb = -nb : 0;
    for (; nb != 0; i++) {
        remains = nb % 10;
        str[i] = remains + '0';
        nb /= 10;
    }
    mem_nb < 0 ? str[i + 1] = '-' : 0;
    str[i] = '\0';
    my_revstr(str);
    return (str);
}