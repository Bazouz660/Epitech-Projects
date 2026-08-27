/*
** EPITECH PROJECT, 2022
** sfsqfsqfs
** File description:
** fqsfsq
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_money_text(core_t *c)
{
    sfColor copper = sfColor_fromRGB(75, 39, 25);

    c->inventory.moneytxt = sfText_create();
    sfText_setFont(c->inventory.moneytxt, c->menu.title_font);
    sfText_setCharacterSize(c->inventory.moneytxt, 50);
    sfText_setFillColor(c->inventory.moneytxt, copper);
}

void money(core_t *c)
{
    sfVector2f ipos = sfSprite_getPosition(c->inventory.book_s);
    sfVector2f pos = {ipos.x + 500, ipos.y + 570};
    char *money = my_int_to_str(c->p.gold);

    sfText_setPosition(c->inventory.moneytxt, pos);
    sfText_setString(c->inventory.moneytxt, money);
    sfRenderWindow_drawText(c->window, c->inventory.moneytxt, NULL);
}