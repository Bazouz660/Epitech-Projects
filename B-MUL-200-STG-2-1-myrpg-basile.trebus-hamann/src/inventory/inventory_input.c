/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** inventory_input.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void handle_click_equip(core_t *c, int i)
{
    if (c->inventory.slots[i].id == 0 && i == 16
        && c->inventory.selected_id != 0
        && c->item[c->inventory.selected_id].type == 2) {
        pickup_item(c, i);
        return;
    } else if (c->inventory.slots[i].id == 0 && i == 17
        && c->inventory.selected_id != 0
        && c->item[c->inventory.selected_id].type == 3) {
        sfSound_play(c->audio.pickup);
        pickup_item(c, i);
        return;
    }
    if (c->inventory.slots[i].id == 0 && i == 18
        && c->inventory.selected_id != 0
        && c->item[c->inventory.selected_id].type == 1) {
        pickup_item(c, i);
        return;
    }
}

void handle_click_inventory(core_t *c, int i)
{
    if (c->inventory.slots[i].id > 0 && c->inventory.selected_id == 0) {
        sfSprite_setTexture(c->inventory.selected_i,
        sfSprite_getTexture(c->inventory.slots[i].obj), True);
        sfSprite_setTexture(c->inventory.slots[i].obj, c->textures.empty, 0);
        c->inventory.mem_slot = i;
        c->inventory.selected_id = c->inventory.slots[i].id;
        c->inventory.slots[i].id = 0;
        return;
    } else if (c->inventory.slots[i].id == 0
        && c->inventory.selected_id != 0 && i < 16) {
        pickup_item(c, i);
        return;
    }
    handle_click_equip(c, i);
}

void handle_selected_item(core_t *c)
{
    static int can_click = 1;

    for (int i = 0; c->inventory.slots[i].rect != NULL; i++) {
        if (get_mouse_intersect_view(c,
            sfRectangleShape_getGlobalBounds(c->inventory.slots[i].rect))
            && sfMouse_isButtonPressed(sfMouseLeft) && can_click == 1) {
            handle_click_inventory(c, i);
            can_click = 0;
        } else if (c->event.type == sfEvtMouseButtonReleased
            && !sfMouse_isButtonPressed(sfMouseLeft))
            can_click = 1;
    }
}

void place_selected_i(core_t *c)
{
    sfVector2f pos = sfSprite_getPosition(c->menu.cursor_s);

    set_sprite_pos(c->inventory.selected_i, pos.x - 20, pos.y - 25);
    sfRenderWindow_drawSprite(c->window, c->inventory.selected_i, NULL);
}
