/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** collisions.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void e_bottom_collision(core_t *c, enemies_t *node)
{
    c->co.global_pos.x = c->co.pbound.left;
    c->co.global_pos.y = c->co.wbound.top - c->co.pbound.height;
    sfRectangleShape_setPosition(node->entity.hitbox, c->co.global_pos);
    node->entity.vect.y = 0;
}

void e_top_collision(core_t *c, enemies_t *node)
{
    c->co.global_pos.x = c->co.pbound.left;
    c->co.global_pos.y = c->co.wbound.top + c->co.wbound.height;
    sfRectangleShape_setPosition(node->entity.hitbox, c->co.global_pos);
    node->entity.vect.y = 0;
}

void e_right_collision(core_t *c, enemies_t *node)
{
    c->co.global_pos.x = c->co.wbound.left - c->co.pbound.width;
    c->co.global_pos.y = c->co.pbound.top;
    sfRectangleShape_setPosition(node->entity.hitbox, c->co.global_pos);
    node->entity.vect.x = 0;
}

void e_left_collision(core_t *c, enemies_t *node)
{
    c->co.global_pos.x = c->co.wbound.left + c->co.wbound.width;
    c->co.global_pos.y = c->co.pbound.top;
    sfRectangleShape_setPosition(node->entity.hitbox, c->co.global_pos);
    node->entity.vect.x = 0;
}
