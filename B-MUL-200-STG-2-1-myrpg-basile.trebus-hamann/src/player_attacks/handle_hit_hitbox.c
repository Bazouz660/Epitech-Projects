/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** handle_hit_hitbox.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void destroy_hitbox(core_t *c)
{
    sfVector2f size = {0, 0};

    sfRectangleShape_setFillColor(c->p.hit_hitbox, sfTransparent);
    sfRectangleShape_setSize(c->p.hit_hitbox, size);
    sfRectangleShape_setOrigin(c->p.hit_hitbox,
    get_rect_center(c->p.hit_hitbox));
    sfRectangleShape_setPosition(c->p.hit_hitbox,
    sfSprite_getPosition(c->p.player));
}

void create_p_hitbox(core_t *c, sfFloatRect bounds)
{
    sfVector2f size = {bounds.width, bounds.height};
    sfVector2f pos = sfSprite_getPosition(c->p.player);

    pos.x += bounds.left;
    pos.y += bounds.top;
    sfRectangleShape_setFillColor(c->p.hit_hitbox, c->color.transparent_red);
    sfRectangleShape_setSize(c->p.hit_hitbox, size);
    sfRectangleShape_setOrigin(c->p.hit_hitbox,
    get_rect_center(c->p.hit_hitbox));
    sfRectangleShape_setPosition(c->p.hit_hitbox, pos);
}

void handle_hit_hitbox(core_t *c)
{
    if (c->pst.attacking == True) {
        get_attack_type(c);
    } else
        destroy_hitbox(c);
}
