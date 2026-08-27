/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** map_panning.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void handle_map_pan(core_t *c)
{
    sfVector2i mouse_pos0 = sfMouse_getPositionRenderWindow(c->window);
    sfVector2f mouse_pos = {mouse_pos0.x + view_bounds(c->view).left,
    mouse_pos0.y + view_bounds(c->view).top};
    static sfVector2f mouse_pos2 = {0, 0};
    float diff = mouse_pos.x - mouse_pos2.x;
    sfVertex *tmp1 = sfVertexArray_getVertex(c->map.m_floor[0].walls[2], 3);
    sfVertex *tmp2 = sfVertexArray_getVertex(c->map.m_floor[0].walls[2], 2);
    sfVertex *tmp3 = sfVertexArray_getVertex(c->map.m_floor[0].walls[2], 0);

    if (sfMouse_isButtonPressed(sfMouseLeft) && mouse_pos.x < \
        (view_bounds(c->view).left + view_bounds(c->view).width) - 1300
        && (tmp2->position.y - 15) > tmp1->position.y)
        rotate_map(c, init_fvect(0, -(float)(diff / 120)));
    else if ((tmp2->position.y - 15) <= tmp1->position.y
        && tmp2->position.x < tmp3->position.x)
        rotate_map(c, init_fvect(0, -0.01));
    if ((tmp2->position.y - 15) <= tmp1->position.y
        && tmp2->position.x > tmp3->position.x)
        rotate_map(c, init_fvect(0, 0.01));
    mouse_pos2 = mouse_pos;
}
