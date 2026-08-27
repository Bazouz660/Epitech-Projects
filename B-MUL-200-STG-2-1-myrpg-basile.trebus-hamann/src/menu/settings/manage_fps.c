/*
** EPITECH PROJECT, 2022
** sqfsqfsqfsq
** File description:
** qfsqffsqf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void manage_30fps(core_t *c)
{
    c->option.button_rect[0].left = 420;
    if (sfMouse_isButtonPressed(sfMouseLeft) != 0 && 
        get_mouse_intersect(c, c->option.fps_sprite[0]) == 1) {
        c->option.button_rect[0].left = 840;
        sfRenderWindow_setFramerateLimit(c->window, 30);
    }
    else if (get_mouse_intersect(c, c->option.fps_sprite[0]) == 0) {
        c->option.button_rect[0].left = 0;
        c->bt_pressed == 1 ? c->bt_pressed = 0 : 0;
    }
    sfSprite_setTextureRect(c->option.fps_sprite[0], c->option.button_rect[0]);
    sfRenderWindow_drawSprite(c->window, c->option.fps_sprite[0], NULL);
}

void manage_60fps(core_t *c)
{
    c->option.button_rect[1].left = 420;
    if (sfMouse_isButtonPressed(sfMouseLeft) != 0 &&
        get_mouse_intersect(c, c->option.fps_sprite[1]) == 1) {
        c->option.button_rect[1].left = 840;
        sfRenderWindow_setFramerateLimit(c->window, 60);
    }
    else if (get_mouse_intersect(c, c->option.fps_sprite[1]) == 0) {
        c->option.button_rect[1].left = 0;
        c->bt_pressed == 2 ? c->bt_pressed = 0 : 0;
    }
    sfSprite_setTextureRect(c->option.fps_sprite[1], c->option.button_rect[1]);
    sfRenderWindow_drawSprite(c->window, c->option.fps_sprite[1], NULL);
}

void manage_90fps(core_t *c)
{
    c->option.button_rect[1].left = 420;
    if (sfMouse_isButtonPressed(sfMouseLeft) != 0 &&
        get_mouse_intersect(c, c->option.fps_sprite[2]) == 1) {
        c->option.button_rect[1].left = 840;
        sfRenderWindow_setFramerateLimit(c->window, 60);
    }
    else if (get_mouse_intersect(c, c->option.fps_sprite[2]) == 0) {
        c->option.button_rect[1].left = 0;
        c->bt_pressed == 3 ? c->bt_pressed = 0 : 0;
    }
    sfSprite_setTextureRect(c->option.fps_sprite[2], c->option.button_rect[1]);
    sfRenderWindow_drawSprite(c->window, c->option.fps_sprite[2], NULL);
}

void manage_120fps(core_t *c)
{
    c->option.button_rect[3].left = 420;
    if (sfMouse_isButtonPressed(sfMouseLeft) != 0 && 
        get_mouse_intersect(c, c->option.fps_sprite[3]) == 1) {
        c->option.button_rect[3].left = 840;
        sfRenderWindow_setFramerateLimit(c->window, 120);
    } else if (get_mouse_intersect(c, c->option.fps_sprite[3]) == 0) {
        c->option.button_rect[3].left = 0;
        c->bt_pressed == 4 ? c->bt_pressed = 0 : 0;
    }
    sfSprite_setTextureRect(c->option.fps_sprite[3], c->option.button_rect[3]);
    sfRenderWindow_drawSprite(c->window, c->option.fps_sprite[3], NULL);
}

void set_alpha_option(core_t *c)
{
    c->color.fade_out.a = 140;
    sfSprite_setColor(c->black_layer, c->color.fade_out);
}
