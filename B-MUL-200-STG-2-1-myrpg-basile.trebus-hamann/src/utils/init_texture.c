/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_texture.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_animated_sprite(sfSprite *sprite, int columns, int rows)
{
    sfIntRect rect = sfSprite_getTextureRect(sprite);
    sfVector2u t_size = sfTexture_getSize(sfSprite_getTexture(sprite));

    rect.left = 0;
    rect.top = 0;
    rect.width = t_size.x / columns;
    rect.height = t_size.y / rows;
    sfSprite_setTextureRect(sprite, rect);
}

void reset_anim(sfSprite *sprite, core_t *c)
{
    sfIntRect sheet_pos = sfSprite_getTextureRect(sprite);

    c->pst.frame_index = 1;
    sheet_pos.top = 0;
    sheet_pos.left = 0;
    sfSprite_setTextureRect(sprite, sheet_pos);
}
