/*
** EPITECH PROJECT, 2022
** sfqsfsq
** File description:
** qsfqsfq
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void float_sound(core_t *c)
{
    if (c->option.bar_scale.x < 0)
        c->option.bar_scale.x = 0;
    if (c->option.bar_scale.x > 400)
        c->option.bar_scale.x = 400;
    if (c->audio.volume > 100)
        c->audio.volume = 100;
    sfRectangleShape_setSize(c->option.bar, c->option.bar_scale);
    sfRenderWindow_drawRectangleShape(c->window, c->option.bar, NULL);
}

void draw_options(core_t *c)
{
    sfRenderWindow_drawSprite(c->window, c->menu.bg_1, NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.embers, NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.bg_2, NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.bg_4, NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.bg_3, NULL);
    sfRenderWindow_drawSprite(c->window, c->black_layer, NULL);
    sfRenderWindow_drawSprite(c->window,c->option.sound_bar_s, NULL);
    float_sound(c);
    manage_settings(c);
    place_cursor(c);
}

void render_options(core_t *c)
{
    draw_options(c);
}
