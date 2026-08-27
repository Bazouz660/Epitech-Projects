/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** get_attack_type.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void get_attack_type_3(core_t *c, sfFloatRect bounds)
{
    if (c->pst.combo == 2) {
        bounds = init_frect(-50 * c->pst.p_direction, 20, 120, 140);
        create_p_hitbox(c, bounds);
        return;
    }
    if (c->pst.combo == 3) {
        bounds = init_frect(-90 * c->pst.p_direction, 20, 140, 100);
        create_p_hitbox(c, bounds);
        return;
    }
    sfRectangleShape_setSize(c->p.hit_hitbox, init_fvect(0, 0));
}

void get_attack_type_2(core_t *c, sfFloatRect bounds)
{
    if (c->pst.run_attack == 1 && c->pst.frame_index == 8) {
        bounds = init_frect(-50 * c->pst.p_direction, 20, 120, 140);
        create_p_hitbox(c, bounds);
        return;
    }
    if (c->pst.jump_attack == 1) {
        bounds = init_frect(-60 * c->pst.p_direction, -50, 120, 120);
        create_p_hitbox(c, bounds);
        return;
    }
    if (c->pst.combo == 1 && c->pst.frame_index == 4) {
        bounds = init_frect(-50 * c->pst.p_direction, 20, 120, 140);
        create_p_hitbox(c, bounds);
        return;
    }
    get_attack_type_3(c, bounds);
}

void get_attack_type(core_t *c)
{
    sfFloatRect bounds;

    if (c->pst.fall_attack == 1) {
        bounds = init_frect(0, 35, 100, 100);
        create_p_hitbox(c, bounds);
        return;
    }
    if (c->pst.fall_attack == 2) {
        bounds = init_frect(0, 65, 300, 60);
        create_p_hitbox(c, bounds);
        return;
    }
    if (c->pst.run_attack == 1 && c->pst.frame_index == 4) {
        bounds = init_frect(-50 * c->pst.p_direction, 20, 120, 140);
        create_p_hitbox(c, bounds);
        return;
    }
    get_attack_type_2(c, bounds);
}
