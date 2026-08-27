/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** stam.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_stam_text(core_t *c)
{
    sfColor copper = sfColor_fromRGB(75, 39, 25);

    c->inventory.stamtxt = sfText_create();
    sfText_setFont(c->inventory.stamtxt, c->menu.title_font);
    sfText_setCharacterSize(c->inventory.stamtxt, 22);
    sfText_setFillColor(c->inventory.stamtxt, sfWhite);
    sfText_setOutlineColor(c->inventory.stamtxt, sfBlack);
    sfText_setOutlineThickness(c->inventory.stamtxt, 1);
}

void stam_inv(core_t *c)
{
    sfVector2f ipos = sfSprite_getPosition(c->inventory.book_s);
    sfVector2f pos = {ipos.x + 240, ipos.y + 556};
    char *stam = my_int_to_str(c->p.stam_inv);

    sfText_setPosition(c->inventory.stamtxt, pos);
    sfText_setString(c->inventory.stamtxt, stam);
    sfRenderWindow_drawText(c->window, c->inventory.stamtxt, NULL);
}
