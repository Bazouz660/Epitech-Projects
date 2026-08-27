/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** collisions.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void bottom_collision(core_t *c, int i)
{
    c->pst.falling = sfFalse;
    c->pst.jumping = sfFalse;
    c->pst.side_jumping = False;
    c->pst.sliding = False;
    c->mv.acceleration = 0;
    c->co.global_pos.x = c->co.pbound.left;
    c->co.global_pos.y = c->co.wbound.top - c->co.pbound.height;
    sfSprite_setPosition(c->p.player_hitbox, c->co.global_pos);
    c->mv.global_vect.y = 0;
    c->mv.global_vect.y < 0 ? c->mv.global_vect.y = 0 : 0;
}

void top_collision(core_t *c, int i)
{
    if (c->pst.memcrouching == sfTrue)
        return crouch(c);
    c->co.global_pos.x = c->co.pbound.left;
    c->co.global_pos.y = c->co.wbound.top + c->co.wbound.height;
    c->co.prev = sfSprite_getPosition(c->p.player_hitbox);
    sfSprite_setPosition(c->p.player_hitbox, c->co.global_pos);
    c->mv.global_vect.y = 0;
}

void right_collision(core_t *c, int i)
{
    c->pst.sprinting = sfFalse;
    check_slide_grab(c);
    c->co.global_pos.x = c->co.wbound.left - c->co.pbound.width;
    c->co.global_pos.y = c->co.pbound.top;
    sfSprite_setPosition(c->p.player_hitbox, c->co.global_pos);
    c->mv.global_vect.x = 0;
}

void left_collision(core_t *c, int i)
{
    c->pst.sprinting = sfFalse;
    check_slide_grab(c);
    c->co.global_pos.x = c->co.wbound.left + c->co.wbound.width;
    c->co.global_pos.y = c->co.pbound.top;
    sfSprite_setPosition(c->p.player_hitbox, c->co.global_pos);
    c->mv.global_vect.x = 0;
}
