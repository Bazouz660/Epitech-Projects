/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** reverse_path.c
*/

#include "../include/solver.h"

void prevnode(solver *s)
{
    if (s->p->prev != NULL) {
        s->p = s->p->prev;
        s->i = s->p->prev->y;
        s->j = s->p->prev->x;
    }
}

vector2 check_y(solver s, char **map, vector2 map_size, int *found)
{
    vector2 move = {-1, -1};

    if (s.i > 0)
        if (map[s.i - 1][s.j] == 'o') {
            *found = 1;
            move.x = s.j;
            move.y = s.i - 1;
        }
    if (s.i < map_size.y - 1)
        if (map[s.i + 1][s.j] == 'o') {
            *found = 1;
            move.x = s.j;
            move.y = s.i + 1;
        }
    return move;
}

vector2 check_x(solver s, char **map, vector2 map_size, int *found)
{
    vector2 move = {-1, -1};

    if (s.j > 0)
        if (map[s.i][s.j - 1] == 'o') {
            *found = 1;
            move.x = s.j - 1;
            move.y = s.i;
        }
    if (s.j < map_size.x - 1)
        if (map[s.i][s.j + 1] == 'o') {
            *found = 1;
            move.x = s.j + 1;
            move.y = s.i;
        }
    return move;
}

vector2 reverse_path(char **map, solver s, vector2 map_size)
{
    int found = 0;
    vector2 move = {0, 0};
    vector2 temp;

    if (map[0][0] == 'R') {
        write(1, "no solution found\n", 13);
        exit(0);
    }
    while (found != 1) {
        prevnode(&s);
        temp = check_y(s, map, map_size, &found);
        if (temp.y != -1)
            move = temp;
        temp = check_x(s, map, map_size, &found);
        if (temp.x != -1)
            move = temp;
    }
    return move;
}
