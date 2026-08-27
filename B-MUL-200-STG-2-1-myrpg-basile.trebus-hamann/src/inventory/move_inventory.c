/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** move_inventory.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void move_rect(core_t *c)
{
    sfVector2f sprite_pos = sfSprite_getPosition(c->inventory.book_s);
    sfVector2f pos = {sprite_pos.x - 1000, sprite_pos.y - 10000};

    sfRectangleShape_setPosition(c->inventory.black_rect, pos);
    sfRenderWindow_drawRectangleShape(c->window, c->inventory.black_rect, NULL);
}

void move_anim_inventory(core_t *c)
{
    sfVector2f pos = {600 + view_bounds(c->view).left,
    200 + view_bounds(c->view).top};

    sfSprite_setPosition(c->inventory.book_s, pos);
    sfRenderWindow_drawSprite(c->window, c->inventory.book_s, NULL);
    if (c->scene_status == 3 && c->shop.trading == 1) {
        set_sprite_pos(c->shop.shop_inv, pos.x + 650, pos.y);
        sfRenderWindow_drawSprite(c->window, c->shop.shop_inv, NULL);
    }
    draw_map(c);
    sfRenderWindow_drawSprite(c->window, c->map.p_logo, NULL);
}

void move_slot(core_t *c, int i, sfVector2f pos)
{
    set_rectshape_pos(c->inventory.slots[i].rect, pos.x, pos.y);
    sfSprite_setPosition(c->inventory.slots[i].obj, pos);
    sfRectangleShape_setFillColor(c->inventory.slots[i].rect,
    c->color.transparent_red);
    if (c->inventory.slots[i].id > 0) {
        sfSprite_setTexture(c->inventory.slots[i].obj,
        c->item[c->inventory.slots[i].id].object_t, True);
        c->inventory.slots[i].stats = \
        c->item[c->inventory.slots[i].id].stats;
    }
}
