/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** fade.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void fade_out(core_t *c, float curb, float time, sfSprite *sprite)
{
    sfColor color = sfSprite_getColor(sprite);

    if (c->clock.seconds > c->menu.fade_out_time + time
        && color.a > 0) {
        c->menu.fade_out_time = c->clock.seconds;
        c->menu.fade_out_curb += curb;
        if (color.a - c->menu.fade_out_curb < 0) {
            c->menu.fade_out_curb = 0;
            color.a = 0;
        }
        color.a -= c->menu.fade_out_curb;
        sfSprite_setColor(sprite, color);
    }
}

void fade_in(core_t *c, sfSprite *sprite)
{
    sfColor color = sfSprite_getColor(sprite);

    if (c->clock.seconds > c->menu.fade_out_time + 0.01
        && color.a < 255) {
        c->menu.fade_in_time = c->clock.seconds;
        c->menu.fade_in_curb += 0.05;
        if (color.a + c->menu.fade_in_curb > 255) {
            c->menu.fade_in_curb = 0;
            color.a = 255;
        }
        color.a += c->menu.fade_in_curb;
        sfSprite_setColor(sprite, color);
    }
}
