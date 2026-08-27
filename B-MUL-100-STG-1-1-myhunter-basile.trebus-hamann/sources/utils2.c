/*
** EPITECH PROJECT, 2021
** utils2.c
** File description:
** utils2
*/

#include "../includes/my_hunter.h"

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
    if (nb < 0) nb = -nb;
    while (nb != 0) {
        remains = nb % 10;
        str[i] = remains + '0';
        nb = nb / 10;
        i = i + 1;
    } if (mem_nb < 0) str[i + 1] = '-';
    str[i] = '\0';
    my_revstr(str);
    return (str);
}

int my_getnbr(char const *str)
{
    int i = 0;
    int n = 0;
    int number = 0;
    int lengh = 0;

    while (str[i] != '\0' && number < 1) {
        if (str[i] >= 48 && str[i] <= 57) {
            while (str[i] >= 48 && str[i] <= 57) {
                n = (n * 10) + str[i] - 48;
                i = i + 1;
                lengh = lengh + 1;
            }
            number = number + 1;
            if (str[i - lengh - 1] == '-')
                n = -1 * n;
        } else {
            i = i + 1;
        }
    }
    return (n);
}

int my_put_nbr(int nb)
{
    int d;

    if (nb < 0) {
        nb = -nb;
        my_putchar('-');
    }
    if (nb > 9) {
        my_put_nbr(nb / 10);
    }
    d = nb % 10 + 48;
    my_putchar(d);
    return (0);
}

int my_strlen_num(char const *str)
{
    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9')
            j++;
        i++;
    }
    return (j);
}