/*
** EPITECH PROJECT, 2022
** tsqff
** File description:
** qfsqfsqf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void manage_up(core_t *c)
{
    c->option.up_rect.left = 70;
    if (sfMouse_isButtonPressed(sfMouseLeft) != 0 && 
        get_mouse_intersect(c, c->option.up_s) == 1) {
        c->option.up_rect.left = 140;
        c->option.bar_scale.x += 10;
        c->audio.volume += 4;
    } else if (get_mouse_intersect(c, c->option.up_s) == 0) {
        c->option.up_rect.left = 0;
    }
    sfSprite_setTextureRect(c->option.up_s, c->option.up_rect);
    sfRenderWindow_drawSprite(c->window, c->option.up_s, NULL);
}

void manage_down(core_t *c)
{
    c->option.down_rect.left = 70;
    if (sfMouse_isButtonPressed(sfMouseLeft) != 0 && 
        get_mouse_intersect(c, c->option.down_s) == 1) {
        c->option.down_rect.left = 140;
        c->option.bar_scale.x -= 10;
        c->audio.volume -= 4;
    } else if (get_mouse_intersect(c, c->option.down_s) == 0) {
        c->option.down_rect.left = 0;
    }
    sfSprite_setTextureRect(c->option.down_s, c->option.down_rect);
    sfRenderWindow_drawSprite(c->window, c->option.down_s, NULL);
}
