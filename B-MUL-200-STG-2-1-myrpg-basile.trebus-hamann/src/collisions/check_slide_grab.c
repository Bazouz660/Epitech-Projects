/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** check_slide_grab.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void check_slide_grab(core_t *c)
{
    if (c->co.pbound.top - 10 > c->co.wbound.top
        && c->co.pbound.top < c->co.wbound.top + (c->co.pbound.height / 3))
        c->pst.can_grab = True;
    else if (c->co.pbound.top - 10 > c->co.wbound.top
        && c->co.pbound.top >= c->co.wbound.top + (c->co.pbound.height / 3)) {
        if ((((sfKeyboard_isKeyPressed(c->keys.left) && c->pst.p_direction == 1)
            || (sfKeyboard_isKeyPressed(c->keys.right)
            && c->pst.p_direction == -1)) && c->pst.grounded == 0)) {
            c->pst.sliding = True;
            c->pst.side_jumping = False;
            c->pst.jumping = False;
            c->pst.falling = False;
        }
        if (c->mv.global_vect.y < MAX_SLIDE_SPD)
            c->mv.global_vect.y = MAX_SLIDE_SPD;
    }
}
