/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** read_usage.c
*/

#include "../includes/my_runner.h"

void read_usage(void)
{
    char *buff;
    int fd = open("misc/README", 0, O_RDONLY);

    buff = malloc(sizeof(char) * 705);
    read(fd, buff, 705);
    write (1, "\n", 1);
    write (1, buff, 705);
    write (1, "\n", 1);
}
