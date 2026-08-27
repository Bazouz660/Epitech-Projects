/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** agility.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_agility_text(core_t *c)
{
    sfColor copper = sfColor_fromRGB(75, 39, 25);

    c->inventory.agilitytxt = sfText_create();
    sfText_setFont(c->inventory.agilitytxt, c->menu.title_font);
    sfText_setCharacterSize(c->inventory.agilitytxt, 22);
    sfText_setFillColor(c->inventory.agilitytxt, sfWhite);
    sfText_setOutlineColor(c->inventory.agilitytxt, sfBlack);
    sfText_setOutlineThickness(c->inventory.agilitytxt, 1);
}

void agility_inv(core_t *c)
{
    sfVector2f ipos = sfSprite_getPosition(c->inventory.book_s);
    sfVector2f pos = {ipos.x + 240, ipos.y + 600};
    char *agility = my_int_to_str(c->p.agility);

    sfText_setPosition(c->inventory.agilitytxt, pos);
    sfText_setString(c->inventory.agilitytxt, agility);
    sfRenderWindow_drawText(c->window, c->inventory.agilitytxt, NULL);
}
