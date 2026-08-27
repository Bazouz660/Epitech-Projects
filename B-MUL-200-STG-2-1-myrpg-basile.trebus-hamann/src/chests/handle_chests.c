/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** handle_chests.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

int find_free_slot(core_t *c)
{
    for (int i = 0; c->inventory.slots[i].rect != NULL; i++) {
        if (c->inventory.slots[i].id == 0 && i < 16)
            return i;
    }
    return -1;
}

void handle_pickup_chest(core_t *c)
{
    sfFloatRect rect1 = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfFloatRect rect2;
    int free_slot;

    for (int i = 0; STAGE.chests[i].sp; i++) {
        rect2 = sfSprite_getGlobalBounds(STAGE.chests[i].sp);
        free_slot = find_free_slot(c);
        if (sfFloatRect_intersects(&rect1, &rect2, NULL)
            && sfKeyboard_isKeyPressed(c->keys.interaction) &&
            sfSprite_getPosition(STAGE.chests[i].loot).y <= \
            sfSprite_getPosition(STAGE.chests[i].sp).y - 10
            && free_slot != -1 && STAGE.chests[i].empty == 0) {
            sfSound_play(c->audio.pickup);
            c->inventory.slots[free_slot].id = STAGE.chests[i].loot_id;
            STAGE.chests[i].empty = True;
        }
    }
}

void handle_chests(core_t *c)
{
    sfFloatRect rect1 = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfFloatRect rect2;

    for (int i = 0; STAGE.chests[i].sp; i++) {
        rect2 = sfSprite_getGlobalBounds(STAGE.chests[i].sp);
        if (sfFloatRect_intersects(&rect1, &rect2, NULL)
            && sfKeyboard_isKeyPressed(c->keys.interaction)
            && STAGE.chests[i].opened == 0) {
            sfSound_play(c->audio.chest_open);
            STAGE.chests[i].opened = 1;
            sfSprite_setTexture(STAGE.chests[i].loot,
            c->item[STAGE.chests[i].loot_id].object_t, True);
            sfSprite_setColor(STAGE.chests[i].loot,
            (sfColor){255, 255, 255, 0});
            sfSprite_setColor(STAGE.chests[i].glow,
            (sfColor){255, 255, 255, 0});
        }
    }
    handle_pickup_chest(c);
}
