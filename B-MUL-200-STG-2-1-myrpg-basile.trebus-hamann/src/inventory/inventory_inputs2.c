/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** inventory_inputs2.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void reset_selected_item(core_t *c)
{
    if (c->inventory.status == 0 && c->inventory.selected_id != 0) {
        sfSprite_setTexture(c->inventory.slots[c->inventory.mem_slot].obj,
        sfSprite_getTexture(c->inventory.selected_i), True);
        c->inventory.slots[c->inventory.mem_slot].id = c->inventory.selected_id;
        c->inventory.selected_id = 0;
        sfSprite_setTexture(c->inventory.selected_i, c->textures.empty, 0);
    }
}

void pickup_item(core_t *c, int i)
{
    c->inventory.mem_slot = 0;
    sfSprite_setTexture(c->inventory.slots[i].obj,
    sfSprite_getTexture(c->inventory.selected_i), True);
    c->inventory.slots[i].id = c->inventory.selected_id;
    c->inventory.selected_id = 0;
    sfSprite_setTexture(c->inventory.selected_i, c->textures.empty, 0);
}
