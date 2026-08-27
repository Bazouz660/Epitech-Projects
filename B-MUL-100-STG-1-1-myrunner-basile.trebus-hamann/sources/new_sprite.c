/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** new_sprite.c
*/

#include "../includes/my_runner.h"

sfSprite *new_sprite(char *texture_name, float x, float y)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f sprite_scale = {x, y};
    sfTexture *sprite_texture = sfTexture_createFromFile(texture_name,
    sfFalse);

    sfSprite_setTexture(sprite, sprite_texture, sfFalse);
    sfSprite_setScale(sprite, sprite_scale);
    return (sprite);
}

sfSprite *new_sprite_looping(char *texture_name, float x, float y)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f sprite_scale = {x, y};
    sfTexture *sprite_texture = sfTexture_createFromFile(texture_name,
    sfFalse);

    sfTexture_setRepeated(sprite_texture, sfTrue);
    sfSprite_setTexture(sprite, sprite_texture, sfFalse);
    sfSprite_setScale(sprite, sprite_scale);
    return (sprite);
}
