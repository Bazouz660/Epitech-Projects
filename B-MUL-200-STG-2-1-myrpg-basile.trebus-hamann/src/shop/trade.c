/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** trade.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void randomise_shop_inventory(core_t *c)
{
    for (int i = 0; i < 8; i++) {
        c->shop.mem_slot = 0;
        c->shop.slots[i].id = c->item[random_between(2, 21)].id;
        sfSprite_setTexture(c->shop.slots[i].obj,
        c->item[c->shop.slots[i].id].object_t, True);
        c->inventory.selected_id = 0;
        sfSprite_setTexture(c->inventory.selected_i, c->textures.empty, 0);
    }
}

void init_trading(core_t *c)
{
    static int can_click = 1;

    if (sfKeyboard_isKeyPressed(c->keys.trade) && can_click == 1) {
        c->shop.trading = 1;
        c->inventory.status = 1;
        can_click = 0;
    }
    else if (c->event.type == sfEvtKeyReleased
        && !sfKeyboard_isKeyPressed(c->keys.trade)) {
        can_click = 1;
    }
    if (c->inventory.status == 0)
        c->shop.trading = 0;
}

void pickup_item_shop(core_t *c, int i)
{
    c->shop.mem_slot = 0;
    sfSprite_setTexture(c->shop.slots[i].obj,
    sfSprite_getTexture(c->inventory.selected_i), True);
    c->shop.slots[i].id = c->inventory.selected_id;
    c->inventory.selected_id = 0;
    sfSprite_setTexture(c->inventory.selected_i, c->textures.empty, 0);
}

void updt_shop_items(core_t *c)
{
    sfVector2f pos;

    for (int i = 0; c->shop.slots[i].rect != NULL; i++) {
        pos = sfRectangleShape_getPosition(c->shop.slots[i].rect);
        sfSprite_setPosition(c->shop.slots[i].obj, pos);
        sfSprite_setTexture(c->shop.slots[i].obj,
        c->item[c->shop.slots[i].id].object_t, True);
    }
}

void handle_click_shop_inv(core_t *c, int i)
{
    if (c->shop.slots[i].id > 0 && c->inventory.selected_id == 0
        && c->p.gold >= c->item[c->shop.slots[i].id].stats.cost) {
        c->p.gold -= c->item[c->shop.slots[i].id].stats.cost;
        sfSprite_setTexture(c->inventory.selected_i,
        sfSprite_getTexture(c->shop.slots[i].obj), True);
        sfSprite_setTexture(c->shop.slots[i].obj, c->textures.empty, 0);
        c->shop.mem_slot = i;
        c->inventory.selected_id = c->shop.slots[i].id;
        c->shop.slots[i].id = 0;
        return;
    } else if (c->shop.slots[i].id == 0
        && c->inventory.selected_id != 0 && i < 16) {
        c->p.gold += c->item[c->inventory.selected_id].stats.cost * 0.75;
        pickup_item_shop(c, i);
        return;
    }
}

void handle_selected_item_shop(core_t *c)
{
    static int can_click = 1;

    for (int i = 0; c->shop.slots[i].rect != NULL; i++) {
        if (get_mouse_intersect_view(c,
            sfRectangleShape_getGlobalBounds(c->shop.slots[i].rect))
            && sfMouse_isButtonPressed(sfMouseLeft) && can_click == 1) {
            handle_click_shop_inv(c, i);
            can_click = 0;
        } else if (c->event.type == sfEvtMouseButtonReleased
            && !sfMouse_isButtonPressed(sfMouseLeft))
            can_click = 1;
    }
}

void handle_trading(core_t *c)
{
    handle_selected_item_shop(c);
    updt_shop_items(c);
}