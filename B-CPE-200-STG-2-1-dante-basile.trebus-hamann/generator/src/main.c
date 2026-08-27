/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** main.c
*/

#include "../include/generator.h"

int my_strlen(char *str)
{
    int res = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        res = res + 1;
    }
    return (res);
}

int convert_str_num(char *str)
{
    int res = 0;
    int calc = 1;
    for (int i = my_strlen(str) - 1; i >= 0; i--) {
        res = res + (str[i] - '0') * calc;
        calc = calc * 10;
    }
    return (res);
}

int main(int ac, char **av)
{
    if (ac < 3) {
        write(2, "Error: must provide a map as argument !\n", 40);
        return 84;
    }
    int x = convert_str_num(av[1]);
    int y = convert_str_num(av[2]);
    my_generator(x, y);
    return (0);
}