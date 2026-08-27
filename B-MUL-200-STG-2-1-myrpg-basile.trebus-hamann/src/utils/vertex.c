/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** vertex.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

sfVertex add_vertex_circular(core_t *c, float *radius,
float i, sfVector2f center)
{
    sfVertex vertex;

    if (i == 0) {
        vertex.color = c->color.light_color;
        vertex.position.x = center.x;
        vertex.position.y = center.y;
        return vertex;
    }
    c->color.light_color.a = 0;
    vertex.color = c->color.light_color;
    vertex.position.x = center.x + *radius * cos(i / 15.5975);
    vertex.position.y = center.y + *radius * sin(i / 15.5975);
    return vertex;
}
