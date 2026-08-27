/*
** EPITECH PROJECT, 2022
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_shop.c
*/

#include "prototypes.h"

void init_door_leave(core_t *c)
{
    sfVector2f pos = {4260, 3710};

    c->shop.door_leaves = sfSprite_create();
    c->shop.door_leavet = sfTexture_createFromFile("sprites/door.png", NULL);
    sfSprite_setTexture(c->shop.door_leaves, c->shop.door_leavet, sfTrue);
    sfSprite_setPosition(c->shop.door_leaves, pos);
}

void init_shop_inv(core_t *c)
{
    c->shop.shop_inv = new_sprite("sprites/shop_inv.png", 0.7, 0.7);
    c->shop.slots = malloc(sizeof(slot_t) * 17);
    for (int i = 0; i < 16; i++) {
        c->shop.slots[i].rect = sfRectangleShape_create();
        c->shop.slots[i].obj = sfSprite_create();
        c->shop.slots[i].id = 0;
        sfRectangleShape_setSize(c->shop.slots[i].rect,
        init_fvect(43, 43));
        sfRectangleShape_setFillColor(c->shop.slots[i].rect,
        c->color.transparent_red);
    }
    c->shop.slots[16].rect = NULL;
}

void init_shop_scene(core_t *c)
{
    sfVector2f size = {300, 100};
    sfVector2f v = sfSprite_getPosition(c->shop.shop_s);
    sfVector2f pos2 = {3257, 1575};
    sfVector2f pos = {0 + view_bounds(c->view).left, -150 +
    view_bounds(c->view).top};
    sfVector2f pos_rect = {5800, 3900};

    c->shop.trading = 0;
    c->shop.shop_entrance = sfRectangleShape_create();
    c->shop.blacksmith_rect = sfRectangleShape_create();
    c->shop.back_s = sfSprite_create();
    c->shop.trade_prompt = new_sprite("sprites/keys/T_Key_Dark.png", 0.7, 0.7);
    c->shop.back_t = sfTexture_createFromFile("sprites/shopinterior.png", NULL);
    sfRectangleShape_setSize(c->shop.blacksmith_rect, size);
    sfRectangleShape_setSize(c->shop.shop_entrance, init_fvect(100, 200));
    sfRectangleShape_setPosition(c->shop.blacksmith_rect, pos_rect);
    sfRectangleShape_setPosition(c->shop.shop_entrance, pos2);
    sfSprite_setTexture(c->shop.back_s, c->shop.back_t, sfTrue);
    sfSprite_setPosition(c->shop.back_s, pos);
    init_door_leave(c);
    init_shop_inv(c);
}
