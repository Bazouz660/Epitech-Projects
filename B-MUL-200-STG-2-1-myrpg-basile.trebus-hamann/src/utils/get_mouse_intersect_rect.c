/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** get_mouse_intersect_rect.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

sfBool mouse_intersect_rect(core_t *c, sfFloatRect rect)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(c->window);
    int posX = rect.left;
    int posY = rect.top;
    int posX_offset = rect.width + rect.left;
    int posY_offset = rect.height + rect.top;

    if ((mouse_pos.x >= posX && mouse_pos.x <= posX_offset)
        && (mouse_pos.y >= posY && mouse_pos.y <= posY_offset))
        return sfTrue;
    else
        return sfFalse;
}

sfBool get_mouse_intersect_view(core_t *c, sfFloatRect to_check)
{
    sfVector2i mouse_pos0 = sfMouse_getPositionRenderWindow(c->window);
    sfVector2f mouse_pos = {mouse_pos0.x + view_bounds(c->view).left,
    mouse_pos0.y + view_bounds(c->view).top};
    int posX = to_check.left;
    int posY = to_check.top;
    int posX_offset = to_check.left + to_check.width;
    int posY_offset = to_check.top + to_check.height;

    if ((mouse_pos.x >= posX && mouse_pos.x <= posX_offset)
        && (mouse_pos.y >= posY && mouse_pos.y <= posY_offset))
        return sfTrue;
    else
        return sfFalse;
}
