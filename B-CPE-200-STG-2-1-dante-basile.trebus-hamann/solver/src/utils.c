/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** utils.c
*/

#include "../include/solver.h"

void init_solver(solver *s, vector2 map_size)
{
    s->sg = malloc(sizeof(solver_grid *) * map_size.y + 1);
    s->solved = 0;
    s->i = 0;
    s->j = 0;
    s->start.x = 0;
    s->start.y = 0;
    s->exit.x = map_size.x - 1;
    s->exit.y = map_size.y - 1;
    s->p = malloc(sizeof(path));
    s->p->next = NULL;
    s->p->x = 0;
    s->p->y = 0;
}

void attach_prev_node(solver *s, int *first)
{
    if (*first == 0) {
        s->p->prev = NULL;
        *first = 1;
        s->lastpos.y = 0;
        s->lastpos.x = 0;
    } else if (s->p->prev != NULL) {
        s->lastpos.y = s->p->prev->y;
        s->lastpos.x = s->p->prev->x;
    }
}

void update_path(char **map, vector2 map_size, solver s)
{
    if ((map[s.move.y][s.move.x] == 'o')) {
        map[s.lastpos.y][s.lastpos.x] = 'R';
        if (is_at_crossroad(map, s, map_size) == 0)
            map[s.move.y][s.move.x] = 'R';
    }
    else if (map[s.move.y][s.move.x] != 'X' && map[s.move.y][s.move.x] != 'R')
        map[s.move.y][s.move.x] = 'o';
}
