/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** animate_passive.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void animate_passive(core_t *c)
{
    if (c->pst.grounded == True && c->mv.global_vect.x == 0
        && c->pst.crouching == False && c->pst.praying == False) {
        play_idle(c);
    } else if (c->pst.grounded == True && c->mv.global_vect.y == 0
        && c->pst.crouching == 0 && c->mv.global_vect.x != 0)
        play_run(c);
    if (c->pst.grounded == False && c->mv.global_vect.y >= 0)
        play_jump(c);
    if (c->pst.grounded == False && c->mv.global_vect.y < 0
        && c->pst.sliding == False)
        play_fall(c);
    if (c->pst.grounded == True && c->mv.global_vect.y == 0
        && c->pst.crouching == True && c->mv.global_vect.x == 0)
        play_idle_crouch(c);
    if (c->pst.grounded == True && c->mv.global_vect.y == 0
        && c->pst.crouching == True && c->mv.global_vect.x != 0)
        play_roll(c);
}

void animate_passive_2(core_t *c)
{
    handle_pray(c);
    if (c->clock.seconds > c->clock.roll_clock + 0.3 && c->pst.rolling == 1) {
        c->pst.rolling = False;
        c->clock.roll_cooldown = c->clock.seconds;
        c->pst.roll_enabled = False;
        uncrouch(c);
    }
    if (c->clock.seconds > c->clock.roll_cooldown + 1.0)
        c->pst.roll_enabled = True;
    if (c->pst.hanging == 1 || (c->pst.sliding == 1
        && c->mv.global_vect.y < -5)) {
        play_hanging(c);
    }
}
