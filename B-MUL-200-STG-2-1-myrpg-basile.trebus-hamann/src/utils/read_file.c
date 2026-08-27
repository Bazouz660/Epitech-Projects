/*
** EPITECH PROJECT, 2022
** qsfqsfqf
** File description:
** sqfqsfsq
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

char* open_text(char *filepath)
{
    char *buffer;
    int fd = open(filepath, O_RDONLY);
    int count = 0;
    char* temp = malloc(sizeof(char) * 1);

    for (; (read(fd, temp, 1) > 0); ++count);
    close(fd);
    fd = open(filepath, O_RDONLY);
    buffer = malloc(sizeof(char) * (count + 1));
    read(fd, buffer, count);
    buffer[count] = '\0';
    close(fd);
    return (buffer);
}