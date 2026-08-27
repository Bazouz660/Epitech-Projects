/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** gravity.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void handle_player_gravity(core_t *c)
{
    if (c->pst.sliding == True && c->mv.global_vect.y < 0)
        c->mv.acceleration = G_FORCE2;
    else
        c->mv.acceleration = G_FORCE;
    if (c->mv.acceleration == G_FORCE2
        && c->mv.global_vect.y - G_FORCE2 > MAX_SLIDE_SPD)
        c->mv.global_vect.y -= c->mv.acceleration;
    else if (c->mv.acceleration == G_FORCE
        && c->mv.global_vect.y - G_FORCE > MAX_FALL_SPD)
        c->mv.global_vect.y -= c->mv.acceleration;
}

static void handle_enemies_gravity(core_t *c, enemies_t *head)
{
    while (head != NULL) {
        c->mv.acceleration = -G_FORCE;
        if (head->entity.vect.y > MAX_FALL_SPD)
            head->entity.vect.y -= c->mv.acceleration;
        head = head->next;
    }
}

void handle_gravity(core_t *c)
{
    if (c->clock.seconds > c->clock.gravity_clock + 0.005) {
        c->clock.gravity_clock = c->clock.seconds;
        if (c->pst.climbing == False)
            handle_player_gravity(c);
        handle_enemies_gravity(c, STAGE.e);
    }
}
