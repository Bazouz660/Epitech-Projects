/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** draw.c
*/

#include "../includes/my_runner.h"

void draw_background(h_p h)
{
    sfRenderWindow_drawSprite(h.window, h.sky_layer, NULL);
    sfRenderWindow_drawSprite(h.window, h.city_layer, NULL);
    sfRenderWindow_drawSprite(h.window, h.tanks_layer, NULL);
    sfRenderWindow_drawSprite(h.window, h.lights_layer, NULL);
    sfRenderWindow_drawSprite(h.window, h.road_layer, NULL);
}

void draw_hud(h_p h)
{
    sfRenderWindow_drawSprite(h.window, h.hud, NULL);
    sfRenderWindow_drawSprite(h.window, h.xina, NULL);
    sfRenderWindow_drawSprite(h.window, h.health_bar, NULL);
    sfRenderWindow_drawText(h.window, h.score_count_text, sfFalse);
}
