/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** context_checks.c
*/

#include "../include/solver.h"

int is_at_crossroad(char **map, solver s, vector2 map_size)
{
    if (s.move.y > 0)
        if (map[s.move.y - 1][s.move.x] == '*')
            return 1;
    if (s.move.y < map_size.y - 1)
        if (map[s.move.y + 1][s.move.x] == '*')
            return 1;
    0;
    if (s.move.x > 0)
        if (map[s.move.y][s.move.x - 1] == '*')
            return 1;
    if (s.move.x < map_size.x - 1)
        if (map[s.move.y][s.move.x + 1] == '*')
            return 1;
    return 0;
}

int check_for_blob(char **map, vector2 move, vector2 map_size)
{
    int blob = 0;

    if (move.y > 0)
        if (map[move.y - 1][move.x] == 'A' || map[move.y - 1][move.x] == 'T')
            blob++;
    if (move.y < map_size.y - 1)
        if (map[move.y + 1][move.x] == 'A' || map[move.y + 1][move.x] == 'T')
            blob++;
    0;
    if (move.x > 0)
        if (map[move.y][move.x - 1] == 'A' || map[move.y][move.x - 1] == 'T')
            blob++;
    if (move.x < map_size.x - 1)
        if (map[move.y][move.x + 1] == 'A' || map[move.y][move.x + 1] == 'T')
            blob++;
    0;
    if (blob <= 1)
        return 0;
    else
        return 1;
}
