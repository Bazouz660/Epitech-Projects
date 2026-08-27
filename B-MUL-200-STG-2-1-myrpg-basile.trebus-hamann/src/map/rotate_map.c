/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** rotate_map.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

sfVector2f rotate_point(sfVector2f pivot, float angle, sfVector2f p,
int inverse)
{
    float s = sin(angle);
    float c = cos(angle);
    float xnew;
    float ynew;
  
    p.x -= pivot.x;
    p.y -= pivot.y;
    xnew = p.x * c - p.y * s;
    ynew = p.x * s + p.y * c;
    p.x = xnew + pivot.x;
    p.y = ynew + pivot.y;
    return p;
}

void incline_floor_2(m_floor_t floor, sfVector2f vect, sfVector2f pos, sfVertex *tmp)
{
    sfVertex *tmp2;
    tmp = sfVertexArray_getVertex(floor.walls[2], 0);
    tmp->position = rotate_point(pos, vect.y, tmp->position, 1);
    tmp = sfVertexArray_getVertex(floor.walls[2], 2);
    tmp->position = rotate_point(pos, vect.y, tmp->position, 1);
    if (!floor.walls[3])
        return;
    tmp = sfVertexArray_getVertex(floor.walls[3], 3);
    tmp2 = sfVertexArray_getVertex(floor.walls[3], 1);;
    pos.x = ((tmp->position.x + tmp2->position.x) / 2);
    pos.y = ((tmp->position.y + tmp2->position.y) / 2);
    tmp = sfVertexArray_getVertex(floor.walls[3], 0);
    tmp->position = rotate_point(pos, vect.y, tmp->position, 1);
    tmp = sfVertexArray_getVertex(floor.walls[3], 2);
    tmp->position = rotate_point(pos, vect.y, tmp->position, 1);
}

void incline_floor(core_t *c, m_floor_t floor, sfVector2f vect)
{
    sfVertex *tmp = sfVertexArray_getVertex(floor.walls[2], 3);
    sfVertex *tmp2 = sfVertexArray_getVertex(floor.walls[2], 1);;
    sfVector2f pos = {((tmp->position.x + tmp2->position.x) / 2),
    ((tmp->position.y + tmp2->position.y) / 2)};

    tmp2 = sfVertexArray_getVertex(floor.walls[0], 2);
    tmp = sfVertexArray_getVertex(floor.walls[0], 2);
    tmp->position = rotate_point(pos, vect.y, tmp->position, 1);
    tmp = sfVertexArray_getVertex(floor.walls[0], 1);
    tmp->position = tmp2->position;
    tmp->position.y -= c->map.size.y;
    tmp2 = sfVertexArray_getVertex(floor.walls[1], 3);
    tmp = sfVertexArray_getVertex(floor.walls[1], 3);
    tmp->position = rotate_point(pos, vect.y, tmp->position, 1);
    tmp = sfVertexArray_getVertex(floor.walls[1], 0);
    tmp->position = tmp2->position;
    tmp->position.y -= c->map.size.y;
    incline_floor_2(floor, vect, pos, tmp);
}

void rotate_map(core_t *c, sfVector2f vect)
{
    for (int i = 0; i < 5; i++) {
        incline_floor(c, c->map.m_floor[i], vect);
    }
}
