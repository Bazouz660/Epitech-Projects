/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** find_cheapest_backtracking.c
*/

#include "../include/solver.h"

vector2 find_cheapest_move_backtracking(char **map, solver s, vector2 map_size)
{
    cheapest_s cs;

    cs.cost = 2000000000;
    cs.found = 0;
    cs.map = map;
    cs.s = s;
    cs.map_size = map_size;
    cs = check_up_backtracking(cs);
    cs = check_down_backtracking(cs);
    cs = check_left_backtracking(cs);
    cs = check_right_backtracking(cs);
    if (cs.found == 0) {
        cs = check_up_backtracking2(cs);
        cs = check_down_backtracking2(cs);
        cs = check_left_backtracking2(cs);
        cs = check_right_backtracking2(cs);
    }
    if (cs.found == 0) {
        cs.move.x = -1;
        cs.move.y = -1;
    }
    return cs.move;
}
