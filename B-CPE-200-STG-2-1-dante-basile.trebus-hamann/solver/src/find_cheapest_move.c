/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** find_cheapest_move.c
*/

#include "../include/solver.h"

cheapest_s check_directions(cheapest_s cs)
{
    cs = check_up(cs);
    cs = check_down(cs);
    cs = check_left(cs);
    cs = check_right(cs);
    return cs;
}

vector2 find_cheapest_move(char **map, solver s, vector2 map_size)
{
    cheapest_s cs;

    cs.cost = 2000000000;
    cs.found = 0;
    cs.map = map;
    cs.s = s;
    cs.map_size = map_size;
    cs = check_directions(cs);
    if (cs.found == 1)
        return cs.move;
    cs.cost = 1000000000;
    cs = check_up2(cs);
    cs = check_down2(cs);
    cs = check_left2(cs);
    cs = check_right2(cs);
    if (cs.found == 1)
        return cs.move;
    cs.move = reverse_path(map, s, map_size);
    return cs.move;
}
