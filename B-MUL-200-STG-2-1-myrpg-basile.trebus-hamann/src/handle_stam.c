/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** handle_stam.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void update_stam_bar(core_t *c)
{
    sfVector2f scale = sfSprite_getScale(c->hud.p_stam.sp_bar_sp);

    scale.x = scale.x * (c->p.stam / c->p.stam_max);
    if (scale.x < 0)
        scale.x = 0;
    sfSprite_setScale(c->hud.p_stam.sp_gbar_sp, scale);
}

void regen_stam(core_t *c)
{
    sfVector2f scale1 = sfSprite_getScale(c->hud.p_stam.sp_bar_sp);
    sfVector2f scale2 = sfSprite_getScale(c->hud.p_stam.sp_gbar_sp);

    if (c->clock.seconds > c->clock.stam_clock + 0.05) {
        c->clock.stam_clock = c->clock.seconds;
        c->p.stam += 1.8 + (c->p.stam_inv / 15);
        if (c->p.stam > c->p.stam_max)
            c->p.stam = c->p.stam_max;
    }
}

void handle_stam(core_t *c)
{
    regen_stam(c);
    update_stam_bar(c);
    if (c->p.stam < 0)
        c->p.stam = 0;
}
