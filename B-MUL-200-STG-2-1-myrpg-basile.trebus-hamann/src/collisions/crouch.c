/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** crouch.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void uncrouch(core_t *c)
{
    c->pst.crouching = sfFalse;
    c->pst.memcrouching = sfTrue;
}

void crouch(core_t *c)
{
    c->pst.crouching = sfTrue;
    c->pst.memcrouching = sfFalse;
}

void handle_crouch(core_t *c)
{
    if (sfKeyboard_isKeyPressed(c->keys.crouch) && c->pst.crouching == False
        && c->pst.grounded == True && c->pst.roll_enabled == sfTrue
        && c->pst.praying == False) {
        cancel_hit(c);
        crouch(c);
    }
    else if ((sfKeyboard_isKeyPressed(c->keys.crouch) == False
        && c->pst.crouching == True && c->pst.rolling == False)
        || (c->pst.grounded == False
        && c->mv.global_vect.y < 0 && c->pst.crouching == True
        && c->pst.rolling == False))
        uncrouch(c);
    if (c->mv.global_vect.x != 0 && c->pst.crouching == True
        && c->pst.rolling == False && c->pst.roll_enabled == True
        && c->p.stam >= 15) {
        c->clock.roll_clock = c->clock.seconds;
        c->p.stam -= 15;
        c->pst.rolling = True;
        sfSound_play(c->audio.roll_sound);
    }
}
