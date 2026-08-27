/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** move_background.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void move_background(core_t *c)
{
    sfVector2f vect = {-c->mv.global_vect.x / 3, -c->mv.global_vect.y};

    vect.y = 0;
    sfSprite_move(c->background, vect);
}

void reset_backgroundy(core_t *c)
{
    sfFloatRect view_rect = view_bounds(c->view);
    sfVector2f temp;
    sfVector2u w_size = sfRenderWindow_getSize(c->window);

    if (sfSprite_getPosition(c->background).y > view_rect.top) {
        temp.x = sfSprite_getPosition(c->background).x;
        temp.y = view_bounds(c->view).top - w_size.y;
        sfSprite_setPosition(c->background, temp);
    }
    if (sfSprite_getPosition(c->background).y + w_size.y < view_rect.top) {
        temp.x = sfSprite_getPosition(c->background).x;
        temp.y = view_bounds(c->view).top;
        sfSprite_setPosition(c->background, temp);
    }
}

void reset_backgroundx(core_t *c)
{
    sfFloatRect view_rect = view_bounds(c->view);
    sfVector2f temp = {-c->mv.global_vect.x, -c->mv.global_vect.y};
    sfVector2u w_size = sfRenderWindow_getSize(c->window);

    if (sfSprite_getPosition(c->background).x > view_rect.left) {
        temp.x = view_bounds(c->view).left - w_size.x;
        temp.y = sfSprite_getPosition(c->background).y;
        sfSprite_setPosition(c->background, temp);
    }
    if (sfSprite_getPosition(c->background).x + w_size.x < view_rect.left) {
        temp.x = view_bounds(c->view).left;
        temp.y = sfSprite_getPosition(c->background).y;
        sfSprite_setPosition(c->background, temp);
    }
}
