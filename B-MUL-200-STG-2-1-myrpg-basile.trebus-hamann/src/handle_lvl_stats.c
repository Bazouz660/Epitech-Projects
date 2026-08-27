/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** handle_lvl_stats.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void handle_exp(core_t *c)
{
    if (c->p.exp >= (c->p.exp_buff + 50) && c->p.level < 100) {
        c->p.level++;
        c->p.exp_buff = c->p.exp;
        c->p.points++;
    }
}

void handle_lvl_stats(core_t *c)
{
    c->p.dmg = 10 + ((0.5 * c->p.strength) *\
    (0.1 * c->item[c->inventory.slots[16].id].stats.dmg_boost));
    c->p.player_speed = 7 + (c->p.agility * 0.02);
    c->p.stam_max = c->p.stam_inv * 20.584;
    if (c->p.stam > c->p.stam_max)
        c->p.stam = c->p.stam_max;
    c->p.health_mem = c->p.vigor * 20.584;
    if (c->p.health > c->p.health_mem)
        c->p.health = c->p.health_mem;
}
