/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** level.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_level_text(core_t *c)
{
    sfColor copper = sfColor_fromRGB(75, 39, 25);

    c->inventory.leveltxt = sfText_create();
    sfText_setFont(c->inventory.leveltxt, c->menu.title_font);
    sfText_setCharacterSize(c->inventory.leveltxt, 30);
    sfText_setFillColor(c->inventory.leveltxt, sfWhite);
    sfText_setOutlineColor(c->inventory.leveltxt, sfBlack);
    sfText_setOutlineThickness(c->inventory.leveltxt, 2);
}

void level_str(core_t *c)
{
    sfVector2f ipos = sfSprite_getPosition(c->inventory.book_s);
    sfVector2f pos = {ipos.x + 200, ipos.y + 240};
    char *level = my_int_to_str(c->p.level);

    sfText_setPosition(c->inventory.leveltxt, pos);
    sfText_setString(c->inventory.leveltxt, level);
    sfRenderWindow_drawText(c->window, c->inventory.leveltxt, NULL);
}
