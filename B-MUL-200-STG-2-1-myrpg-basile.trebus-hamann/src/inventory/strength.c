/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** strength.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_strength_text(core_t *c)
{
    sfColor copper = sfColor_fromRGB(75, 39, 25);

    c->inventory.strengthtxt = sfText_create();
    sfText_setFont(c->inventory.strengthtxt, c->menu.title_font);
    sfText_setCharacterSize(c->inventory.strengthtxt, 22);
    sfText_setFillColor(c->inventory.strengthtxt, sfWhite);
    sfText_setOutlineColor(c->inventory.strengthtxt, sfBlack);
    sfText_setOutlineThickness(c->inventory.strengthtxt, 1);
}

void strength_inv(core_t *c)
{
    sfVector2f ipos = sfSprite_getPosition(c->inventory.book_s);
    sfVector2f pos = {ipos.x + 240, ipos.y + 578};
    char *strength = my_int_to_str(c->p.strength);

    sfText_setPosition(c->inventory.strengthtxt, pos);
    sfText_setString(c->inventory.strengthtxt, strength);
    sfRenderWindow_drawText(c->window, c->inventory.strengthtxt, NULL);
}
