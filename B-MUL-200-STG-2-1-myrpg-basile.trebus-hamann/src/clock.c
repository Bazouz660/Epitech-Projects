/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** clock.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void update_clock(core_t *c)
{
    c->clock.time = sfClock_getElapsedTime(c->clock.clock);
    c->clock.seconds = c->clock.time.microseconds/1000000.0;
}
