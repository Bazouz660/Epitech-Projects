/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** check_directions.c
*/

#include "../include/solver.h"

cheapest_s check_up(cheapest_s cs)
{
    if (cs.s.i > 0 && cs.s.i < cs.map_size.y) {
        cs.s.sg[cs.s.i - 1][cs.s.j].g = 0;
        cs.s.sg[cs.s.i - 1][cs.s.j].h = find_distance_exit(cs.map_size,
        cs.s.i - 1, cs.s.j);
        cs.s.sg[cs.s.i - 1][cs.s.j].cost = cs.s.sg[cs.s.i - 1][cs.s.j].h;
        if ((cs.cost > cs.s.sg[cs.s.i - 1][cs.s.j].cost
            && cs.map[cs.s.i - 1][cs.s.j] != 'X'
            && cs.map[cs.s.i - 1][cs.s.j] != 'R'
            && cs.map[cs.s.i - 1][cs.s.j] != 'o')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i - 1][cs.s.j].cost;
            cs.move.x = cs.s.j;
            cs.move.y = cs.s.i - 1;
        }
    }
    return cs;
}

cheapest_s check_down(cheapest_s cs)
{
    if (cs.s.i < cs.map_size.y - 1) {
        cs.s.sg[cs.s.i + 1][cs.s.j].g = 0;
        cs.s.sg[cs.s.i + 1][cs.s.j].h = find_distance_exit(cs.map_size,
        cs.s.i + 1, cs.s.j);
        cs.s.sg[cs.s.i + 1][cs.s.j].cost = cs.s.sg[cs.s.i + 1][cs.s.j].h;
        if ((cs.cost > cs.s.sg[cs.s.i + 1][cs.s.j].cost
            && cs.map[cs.s.i + 1][cs.s.j] != 'X'
            && cs.map[cs.s.i + 1][cs.s.j] != 'R'
            && cs.map[cs.s.i + 1][cs.s.j] != 'o')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i + 1][cs.s.j].cost;
            cs.move.x = cs.s.j;
            cs.move.y = cs.s.i + 1;
        }
    }
    return cs;
}

cheapest_s check_left(cheapest_s cs)
{
    if (cs.s.j > 0 && cs.s.j < cs.map_size.y) {
        cs.s.sg[cs.s.i][cs.s.j - 1].g = 0;
        cs.s.sg[cs.s.i][cs.s.j - 1].h = find_distance_exit(cs.map_size,
        cs.s.i, cs.s.j - 1);
        cs.s.sg[cs.s.i][cs.s.j - 1].cost = cs.s.sg[cs.s.i][cs.s.j - 1].h;
        if ((cs.cost > cs.s.sg[cs.s.i][cs.s.j - 1].cost
            && cs.map[cs.s.i][cs.s.j - 1] != 'X'
            && cs.map[cs.s.i][cs.s.j - 1] != 'R'
            && cs.map[cs.s.i][cs.s.j - 1] != 'o')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i][cs.s.j - 1].cost;
            cs.move.x = cs.s.j - 1;
            cs.move.y = cs.s.i;
        }
    }
    return cs;
}

cheapest_s check_right(cheapest_s cs)
{
    if (cs.s.j < cs.map_size.x - 1) {
        cs.s.sg[cs.s.i][cs.s.j + 1].g = 0;
        cs.s.sg[cs.s.i][cs.s.j + 1].h = find_distance_exit(cs.map_size,
        cs.s.i, cs.s.j + 1);
        cs.s.sg[cs.s.i][cs.s.j + 1].cost = cs.s.sg[cs.s.i][cs.s.j + 1].h;
        if ((cs.cost > cs.s.sg[cs.s.i][cs.s.j + 1].cost
            && cs.map[cs.s.i][cs.s.j + 1] != 'X'
            && cs.map[cs.s.i][cs.s.j + 1] != 'R'
            && cs.map[cs.s.i][cs.s.j + 1] != 'o')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i][cs.s.j + 1].cost;
            cs.move.x = cs.s.j + 1;
            cs.move.y = cs.s.i;
        }
    }
    return cs;
}
