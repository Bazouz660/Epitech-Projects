/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** points.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_points_text(core_t *c)
{
    sfColor copper = sfColor_fromRGB(75, 39, 25);

    c->inventory.pointstxt = sfText_create();
    sfText_setFont(c->inventory.pointstxt, c->menu.title_font);
    sfText_setCharacterSize(c->inventory.pointstxt, 24);
    sfText_setFillColor(c->inventory.pointstxt, sfWhite);
    sfText_setOutlineColor(c->inventory.pointstxt, sfBlack);
    sfText_setOutlineThickness(c->inventory.pointstxt, 1);
}

void points_inv(core_t *c)
{
    sfVector2f ipos = sfSprite_getPosition(c->inventory.book_s);
    sfVector2f pos = {ipos.x + 260, ipos.y + 630};
    char *points = my_int_to_str(c->p.points);

    sfText_setPosition(c->inventory.pointstxt, pos);
    sfText_setString(c->inventory.pointstxt, points);
    sfRenderWindow_drawText(c->window, c->inventory.pointstxt, NULL);
}
