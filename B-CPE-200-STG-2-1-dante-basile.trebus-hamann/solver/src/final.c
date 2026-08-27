/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** final.c
*/

#include "../include/solver.h"

char **clean_map(char **map, vector2 map_size)
{
    int lengh = 0;

    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; j < map_size.x; j++) {
            (map[i][j] != 'X' && map[i][j] != '*'
            && map[i][j] != 'A') ? map[i][j] = '*' : 0;
        }
    for (int i = 0; map[i] != NULL; i++)
        for (int j = 0; j < map_size.x; j++)
            map[i][j] == 'A' ? map[i][j] = 'o' : 0;
    return map;
}

void print_map(char **map, vector2 map_size)
{
    for (int i = 0; map[i] != NULL; i++) {
        write(1, map[i], strlen(map[i]));
        if (map[i + 1] != NULL)
            write(1, "\n", 1);
    }
}
