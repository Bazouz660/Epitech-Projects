/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** read_file.c
*/

#include "../include/solver.h"

char *read_file(char *location)
{
    int fd = open(location, O_RDONLY);
    int buffer_size = 1;
    char *str = malloc(sizeof(char) * 1);

    if (fd == -1) {
        write(2, "Error: cannot open '", 20);
        write(2, location, strlen(location));
        write(2, "': No such file or directory\n", 29);
        exit(84);
    }
    for (; read(fd, str, 1); buffer_size++)
        str = malloc(sizeof(char) * buffer_size + 1);
    fd = open(location, O_RDONLY);
    if (read(fd, str, buffer_size) == -1)
        exit(84);
    str = strcat(str, "\n");
    return str;
}
