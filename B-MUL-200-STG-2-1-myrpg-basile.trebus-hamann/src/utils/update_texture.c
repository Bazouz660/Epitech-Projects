/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** animated_sprite.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

sfSprite *update_animated_spritev(sfSprite *sprite)
{
    sfIntRect sheet_pos = sfSprite_getTextureRect(sprite);

    sheet_pos.top += sheet_pos.height;
    sheet_pos.left = 0;
    sfSprite_setTextureRect(sprite, sheet_pos);
    return (sprite);
}

void upone(update_sprite_t *up)
{
    if (up->sheet_pos.left != 0)
        if (up->sheet_pos.left / up->sheet_pos.width <= up->frames.x
            && up->frames.y > 1) {
            up->sheet_pos.top += up->sheet_pos.height;
            up->sheet_pos.left = 0;
            up->y = 1;
        }
    up->y == 0 ? up->sheet_pos.left += up->sheet_pos.width : 0;
}

void updtwo(update_sprite_t *up, sfSprite *sprite)
{
    if (up->sheet_pos.left <= up->txtr_size.x
        && up->sheet_pos.top >= up->txtr_size.y) {
        up->sheet_pos.left = 0;
        up->sheet_pos.top = 0;
    }
    sfSprite_setTextureRect(sprite, up->sheet_pos);
}

int upt_anim_sprite(sfSprite *sprite, sfVector2i frames,
sfBool looping, int frame_index)
{
    update_sprite_t up;

    if (frame_index == (frames.x * frames.y)) {
        if (looping == False)
            return frame_index;
        frame_index = 1;
    }
    up.sheet_pos = sfSprite_getTextureRect(sprite);
    up.txtr_size = sfTexture_getSize(sfSprite_getTexture(sprite));
    up.y = 0;
    up.sprite = sprite;
    up.frames.x = frames.x;
    up.frames.y = frames.y;
    up.looping = looping;
    upone(&up);
    updtwo(&up, sprite);
    frame_index++;
    return frame_index;
}
