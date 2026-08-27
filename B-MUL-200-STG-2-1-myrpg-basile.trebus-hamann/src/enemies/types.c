/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** types.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_type2(core_t *c, entity_t *entity)
{
    sfVector2f pos = {1400, 2600};
    sfVector2f size = {50, 85};

    entity->hit_hitbox = sfRectangleShape_create();
    sfRectangleShape_setPosition(entity->hit_hitbox, pos);
    sfRectangleShape_setSize(entity->hit_hitbox, size);
    sfRectangleShape_setFillColor(entity->hit_hitbox, sfRed);
    entity->sprite = sfSprite_create();
}

void create_type3(core_t *c, entity_t *entity)
{
    sfVector2f pos = {1200, 2600};
    sfVector2f size = {50, 85};

    entity->hit_hitbox = sfRectangleShape_create();
    sfRectangleShape_setPosition(entity->hit_hitbox, pos);
    sfRectangleShape_setSize(entity->hit_hitbox, size);
    sfRectangleShape_setFillColor(entity->hit_hitbox, sfRed);
    entity->sprite = sfSprite_create();
}

void create_type4(core_t *c, entity_t *entity)
{
    sfVector2f pos = {1000, 2600};
    sfVector2f size = {50, 85};

    entity->hit_hitbox = sfRectangleShape_create();
    sfRectangleShape_setPosition(entity->hit_hitbox, pos);
    sfRectangleShape_setSize(entity->hit_hitbox, size);
    sfRectangleShape_setFillColor(entity->hit_hitbox, sfRed);
    entity->sprite = sfSprite_create();
}
