/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** pray.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void handle_pray(core_t *c)
{
    if (c->pst.grounded == 1 && c->mv.global_vect.y == 0
        && c->mv.global_vect.x == 0 && c->pst.praying == True
        && c->pst.pray_end == False && c->pst.crouching == 0) {
        if (c->pst.pray_state < 1) {
            play_pray_start(c);
        } else
            play_pray_idle(c);
    }
    if (c->clock.seconds > c->clock.pray_clock + 4.0 && c->pst.praying == 1) {
        if (c->pst.pray_end == False)
            c->pst.pray_state = 0;
        c->pst.pray_end = True;
        play_pray_end(c);
        if (c->pst.pray_state >= 1) {
            c->clock.pray_clock = c->clock.seconds;
            c->pst.praying = False;
            c->pst.pray_end = False;
            c->pst.pray_state = 0;
        }
    }
}
