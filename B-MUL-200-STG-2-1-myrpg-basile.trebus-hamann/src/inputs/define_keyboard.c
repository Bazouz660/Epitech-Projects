/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** define_keyboard.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_keyboard(core_t *c)
{
    c->keys.up = sfKeyZ;
    c->keys.down = sfKeyS;
    c->keys.right = sfKeyD;
    c->keys.left = sfKeyQ;
    c->keys.crouch = sfKeyLControl;
    c->keys.sprint = sfKeyLShift;
    c->keys.jump = sfKeySpace;
    c->keys.pray = sfKeyE;
    c->keys.pause = sfKeyP;
    c->keys.unpause = sfKeyR;
    c->keys.inventory = sfKeyI;
    c->keys.back = sfKeyEscape;
    c->keys.skip = sfKeyEnter;
    c->keys.can_click = True;
    c->keys.interaction = sfKeyE;
    c->keys.trade = sfKeyT;
}