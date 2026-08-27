/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** respawn.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void handle_respawn(core_t *c)
{
    sfColor color;

    if (c->p.health <= 0)
        if (c->clock.seconds > c->clock.respawn_clock + 5.5) {
            c->menu.fade_in_curb = 0;
            c->clock.respawn_clock = c->clock.seconds;
            c->p.health = c->p.health_mem;
            color = sfSprite_getColor(c->you_died);
            color.a = 0;
            sfSprite_setColor(c->you_died, color);
            color = sfSprite_getColor(c->black_layer);
            color.a = 255;
            sfSprite_setColor(c->black_layer, color);
            color = sfSprite_getColor(c->p_saved);
            color.a = 0;
            c->color.fade_in.a = 0;
            sfSprite_setColor(c->p_saved, color);
            reset_enemies(c, STAGE.e);
            sfSprite_setPosition(c->p.player_hitbox, c->save.last_camp);
        }
}