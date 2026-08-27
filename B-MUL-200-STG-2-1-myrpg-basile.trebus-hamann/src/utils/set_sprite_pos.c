/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** set_sprite_pos.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

sfSprite *set_sprite_pos(sfSprite *sprite, float posX, float posY)
{
    sfVector2f pos = {posX, posY};

    sfSprite_setPosition(sprite, pos);
    return (sprite);
}

void *set_rectshape_pos(sfRectangleShape *rect, float posX, float posY)
{
    sfVector2f pos = {posX, posY};

    sfRectangleShape_setPosition(rect, pos);
}
