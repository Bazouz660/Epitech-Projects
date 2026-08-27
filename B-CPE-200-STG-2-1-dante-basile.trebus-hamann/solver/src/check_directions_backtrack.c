/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** check_directions_backtracking.c
*/

#include "../include/solver.h"

cheapest_s check_up_backtracking(cheapest_s cs)
{
    if (cs.s.i > 0 && cs.s.i < cs.map_size.y) {
        cs.s.sg[cs.s.i - 1][cs.s.j].g = 0;
        cs.s.sg[cs.s.i - 1][cs.s.j].h = find_distance_entry(cs.map_size,
        cs.s.i - 1, cs.s.j);
        cs.s.sg[cs.s.i - 1][cs.s.j].cost = cs.s.sg[cs.s.i - 1][cs.s.j].h;
        if (cs.cost > cs.s.sg[cs.s.i - 1][cs.s.j].cost
            && (cs.map[cs.s.i - 1][cs.s.j] == 'o')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i - 1][cs.s.j].cost;
            cs.move.x = cs.s.j;
            cs.move.y = cs.s.i - 1;
        }
    }
    return cs;
}

cheapest_s check_down_backtracking(cheapest_s cs)
{
    if (cs.s.i < cs.map_size.y - 1) {
        cs.s.sg[cs.s.i + 1][cs.s.j].g = 0;
        cs.s.sg[cs.s.i + 1][cs.s.j].h = find_distance_entry(cs.map_size,
        cs.s.i + 1, cs.s.j);
        cs.s.sg[cs.s.i + 1][cs.s.j].cost = cs.s.sg[cs.s.i + 1][cs.s.j].h;
        if (cs.cost > cs.s.sg[cs.s.i + 1][cs.s.j].cost
            && (cs.map[cs.s.i + 1][cs.s.j] == 'o')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i + 1][cs.s.j].cost;
            cs.move.x = cs.s.j;
            cs.move.y = cs.s.i + 1;
        }
    }
    return cs;
}

cheapest_s check_left_backtracking(cheapest_s cs)
{
    if (cs.s.j > 0) {
        cs.s.sg[cs.s.i][cs.s.j - 1].g = 0;
        cs.s.sg[cs.s.i][cs.s.j - 1].h = find_distance_entry(cs.map_size,
        cs.s.i, cs.s.j - 1);
        cs.s.sg[cs.s.i][cs.s.j - 1].cost = cs.s.sg[cs.s.i][cs.s.j - 1].h;
        if (cs.cost > cs.s.sg[cs.s.i][cs.s.j - 1].cost
            && (cs.map[cs.s.i][cs.s.j - 1] == 'o')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i][cs.s.j - 1].cost;
            cs.move.x = cs.s.j - 1;
            cs.move.y = cs.s.i;
        }
    }
    return cs;
}

cheapest_s check_right_backtracking(cheapest_s cs)
{
    if (cs.s.j < cs.map_size.x - 1) {
        cs.s.sg[cs.s.i][cs.s.j + 1].g = 0;
        cs.s.sg[cs.s.i][cs.s.j + 1].h = find_distance_entry(cs.map_size,
        cs.s.i, cs.s.j + 1);
        cs.s.sg[cs.s.i][cs.s.j + 1].cost = cs.s.sg[cs.s.i][cs.s.j + 1].h;
        if (cs.cost > cs.s.sg[cs.s.i][cs.s.j + 1].cost
            && (cs.map[cs.s.i][cs.s.j + 1] == 'o')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i][cs.s.j + 1].cost;
            cs.move.x = cs.s.j + 1;
            cs.move.y = cs.s.i;
        }
    }
    return cs;
}

cheapest_s check_up_backtracking2(cheapest_s cs)
{
    if (cs.s.i > 0 && cs.s.i < cs.map_size.y) {
        cs.s.sg[cs.s.i - 1][cs.s.j].g = 0;
        cs.s.sg[cs.s.i - 1][cs.s.j].h = find_distance_entry(cs.map_size,
        cs.s.i - 1, cs.s.j);
        cs.s.sg[cs.s.i - 1][cs.s.j].cost = cs.s.sg[cs.s.i - 1][cs.s.j].h;
        if (cs.cost > cs.s.sg[cs.s.i - 1][cs.s.j].cost
            && (cs.map[cs.s.i - 1][cs.s.j] == 'R')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i - 1][cs.s.j].cost;
            cs.move.x = cs.s.j;
            cs.move.y = cs.s.i - 1;
        }
    }
    return cs;
}

cheapest_s check_down_backtracking2(cheapest_s cs)
{
    if (cs.s.i < cs.map_size.y - 1) {
        cs.s.sg[cs.s.i + 1][cs.s.j].g = 0;
        cs.s.sg[cs.s.i + 1][cs.s.j].h = find_distance_entry(cs.map_size,
        cs.s.i + 1, cs.s.j);
        cs.s.sg[cs.s.i + 1][cs.s.j].cost = cs.s.sg[cs.s.i + 1][cs.s.j].h;
        if (cs.cost > cs.s.sg[cs.s.i + 1][cs.s.j].cost
            && (cs.map[cs.s.i + 1][cs.s.j] == 'R')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i + 1][cs.s.j].cost;
            cs.move.x = cs.s.j;
            cs.move.y = cs.s.i + 1;
        }
    }
    return cs;
}

cheapest_s check_left_backtracking2(cheapest_s cs)
{
    if (cs.s.j > 0) {
        cs.s.sg[cs.s.i][cs.s.j - 1].g = 0;
        cs.s.sg[cs.s.i][cs.s.j - 1].h = find_distance_entry(cs.map_size,
        cs.s.i, cs.s.j - 1);
        cs.s.sg[cs.s.i][cs.s.j - 1].cost = cs.s.sg[cs.s.i][cs.s.j - 1].h;
        if (cs.cost > cs.s.sg[cs.s.i][cs.s.j - 1].cost
            && (cs.map[cs.s.i][cs.s.j - 1] == 'R')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i][cs.s.j - 1].cost;
            cs.move.x = cs.s.j - 1;
            cs.move.y = cs.s.i;
        }
    }
    return cs;
}

cheapest_s check_right_backtracking2(cheapest_s cs)
{
    if (cs.s.j < cs.map_size.x - 1) {
        cs.s.sg[cs.s.i][cs.s.j + 1].g = 0;
        cs.s.sg[cs.s.i][cs.s.j + 1].h = find_distance_entry(cs.map_size,
        cs.s.i, cs.s.j + 1);
        cs.s.sg[cs.s.i][cs.s.j + 1].cost = cs.s.sg[cs.s.i][cs.s.j + 1].h;
        if (cs.cost > cs.s.sg[cs.s.i][cs.s.j + 1].cost
            && (cs.map[cs.s.i][cs.s.j + 1] == 'R')) {
            cs.found = 1;
            cs.cost = cs.s.sg[cs.s.i][cs.s.j + 1].cost;
            cs.move.x = cs.s.j + 1;
            cs.move.y = cs.s.i;
        }
    }
    return cs;
}
