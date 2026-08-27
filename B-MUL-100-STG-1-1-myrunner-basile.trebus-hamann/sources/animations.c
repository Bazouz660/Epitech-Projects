/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** animations.c
*/

#include "../includes/my_runner.h"

sfSprite *update_animated_sprite(sfSprite *sprite,
int offset, int width, int height)
{
    sfIntRect sheet_pos = {offset, 0, width, height};

    sfSprite_setTextureRect(sprite, sheet_pos);
    return (sprite);
}

sfSprite *update_animated_sprite_v(sfSprite *sprite,
int offset, int width, int height)
{
    sfIntRect sheet_pos = {0, offset, width, height};

    sfSprite_setTextureRect(sprite, sheet_pos);
    return (sprite);
}

h_p animate_background(h_p h)
{
    update_animated_sprite(h.sky_layer, 0 + (h.counter * 0.5), 1920, 1080);
    update_animated_sprite(h.tanks_layer, 0 + (h.counter * 2), 1920, 1080);
    update_animated_sprite(h.road_layer, 0 + (h.counter * 1.5),
    1920, 1080);
    update_animated_sprite(h.city_layer, 0 + (h.counter * 0.8),
    1920, 1080);
    update_animated_sprite(h.lights_layer, 0 + (h.counter * 1.5),
    1920, 1080);
    h.counter += 2;
    return h;
}

h_p animate_character(h_p h)
{
    static int offset = 0;
    static int idle_anim = 0;

    if (h.sliding == 1)
       offset = 0;
    h.player_pos = h.player_pos;
    if (((h.seconds - h.r_1) >= (0.1 - h.anim_speed_offset)) 
        && h.sliding == 0) {
        update_animated_sprite(h.tank_man, offset, 64, 64);
        offset += 64;
        h.r_1 = h.seconds;
    }
    return h;
}
