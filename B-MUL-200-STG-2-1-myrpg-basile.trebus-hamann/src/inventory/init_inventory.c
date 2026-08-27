/*
** EPITECH PROJECT, 2022
** ffqsfqsfsq
** File description:
** qsfsfsq
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_inv_slots(core_t *c)
{
    c->inventory.slots = malloc(sizeof(slot_t) * 20);

    for (int i = 0; i < 19; i++) {
        c->inventory.slots[i].rect = sfRectangleShape_create();
        c->inventory.slots[i].obj = sfSprite_create();
        c->inventory.slots[i].id = 0;
        sfRectangleShape_setSize(c->inventory.slots[i].rect,
        init_fvect(43, 43));
        sfRectangleShape_setFillColor(c->inventory.slots[i].rect,
        c->color.transparent_red);
    }
    c->inventory.slots[19].rect = NULL;
}

void init_black(core_t *c)
{
    sfVector2f size = {50000, 50000};
    sfColor black = sfColor_fromRGBA(0, 0, 0, 140);

    c->inventory.black_rect = sfRectangleShape_create();
    sfRectangleShape_setSize (c->inventory.black_rect, size);
    sfRectangleShape_setFillColor(c->inventory.black_rect, black);
}

void init_book(core_t *c)
{
    sfVector2f scale = {0.7, 0.7};
    c->inventory.book_s = sfSprite_create();
    c->inventory.book_t = sfTexture_createFromFile("sprites/inventory.png",
    NULL);
    sfSprite_setTexture(c->inventory.book_s, c->inventory.book_t, sfTrue);
    sfSprite_setScale(c->inventory.book_s, scale);
}

void init_descriptor(core_t *c)
{
    c->inventory.desc.bg = new_sprite("sprites/desc.png", 0.261, 0.261);
    init_sftext(c, &c->inventory.desc.txt_armor, 23);
    init_sftext(c, &c->inventory.desc.txt_dmg, 23);
    init_sftext(c, &c->inventory.desc.txt_life_reg, 23);
    init_sftext(c, &c->inventory.desc.txt_xp_gain, 23);
    init_sftext(c, &c->inventory.desc.txt_cost, 23);
}

void create_plus(core_t *c)
{
    c->inventory.plus_1 = new_sprite("sprites/plus.png", 0.22, 0.22);
    c->inventory.plus_2 = sfSprite_copy(c->inventory.plus_1);
    c->inventory.plus_3 = sfSprite_copy(c->inventory.plus_1);
    c->inventory.plus_4 = sfSprite_copy(c->inventory.plus_1);
}

void init_inventory(core_t *c)
{
    c->inventory.status = 0;
    init_black(c);
    init_book(c);
    init_item(c);
    init_inv_slots(c);
    init_descriptor(c);
    create_plus(c);
    create_money_text(c);
    create_level_text(c);
    create_vigor_text(c);
    create_stam_text(c);
    create_strength_text(c);
    create_agility_text(c);
    create_points_text(c);
    c->inventory.selected_i = sfSprite_create();
    c->inventory.selected_id = 0;
}
