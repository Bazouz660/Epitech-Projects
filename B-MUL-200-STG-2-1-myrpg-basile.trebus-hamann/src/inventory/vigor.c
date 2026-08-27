/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** vigor.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_vigor_text(core_t *c)
{
    sfColor copper = sfColor_fromRGB(75, 39, 25);

    c->inventory.vigortxt = sfText_create();
    sfText_setFont(c->inventory.vigortxt, c->menu.title_font);
    sfText_setCharacterSize(c->inventory.vigortxt, 22);
    sfText_setFillColor(c->inventory.vigortxt, sfWhite);
    sfText_setOutlineColor(c->inventory.vigortxt, sfBlack);
    sfText_setOutlineThickness(c->inventory.vigortxt, 1);
}

void vigor_inv(core_t *c)
{
    sfVector2f ipos = sfSprite_getPosition(c->inventory.book_s);
    sfVector2f pos = {ipos.x + 240, ipos.y + 532};
    char *vigor = my_int_to_str(c->p.vigor);

    sfText_setPosition(c->inventory.vigortxt, pos);
    sfText_setString(c->inventory.vigortxt, vigor);
    sfRenderWindow_drawText(c->window, c->inventory.vigortxt, NULL);
}
