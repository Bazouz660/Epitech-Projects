/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** right_left_mvt.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void inv_player_direction(core_t *c)
{
        c->p.player_scale = sfSprite_getScale(c->p.player);
        c->p.player_scale.x *= -1;
        c->pst.p_direction *= -1;
        sfSprite_setScale(c->p.player, c->p.player_scale);
}

void move_right(core_t *c)
{
    c->mv.global_vect.x = -c->p.player_speed;
    c->pst.moving = True;
    if (c->pst.p_direction == 1) {
        if (c->pst.sprinting == True && c->pst.grounded == False)
            c->pst.sprinting = False;
        inv_player_direction(c);
    }
}

void move_left(core_t *c)
{
    c->mv.global_vect.x = c->p.player_speed;
    c->pst.moving = True;
    if (c->pst.p_direction == -1) {
        if (c->pst.sprinting == True && c->pst.grounded == False)
            c->pst.sprinting = False;
        inv_player_direction(c);
    }
}

void direction_handler(core_t *c)
{
    if (sfKeyboard_isKeyPressed(c->keys.right)
        && c->pst.rolling == False && c->pst.praying == False
        && c->pst.side_jumping == False) {
        if (c->pst.attacking == True && c->mv.global_vect.x == 0)
            cancel_hit(c);
        return move_right(c);
    }
    if (sfKeyboard_isKeyPressed(c->keys.left)
        && c->pst.rolling == False && c->pst.praying == False
        && c->pst.side_jumping == False) {
        if (c->pst.attacking == True && c->mv.global_vect.x == 0)
            cancel_hit(c);
        return move_left(c);
    }
    if (c->pst.grounded == True) {
        c->pst.moving = False;
        c->mv.global_vect.x = 0;
    }
}
