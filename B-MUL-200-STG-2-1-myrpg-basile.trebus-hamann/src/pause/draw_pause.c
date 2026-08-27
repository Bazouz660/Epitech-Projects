/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** draw_pause.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void render_pause_menu(core_t *c)
{
    sfRenderWindow_drawRectangleShape(c->window, c->inventory.black_rect, NULL);
    sfRenderWindow_drawSprite(c->window, c->p_menu.bg, NULL);
    sfRenderWindow_drawSprite(c->window, c->p_menu.resume, NULL);
    sfRenderWindow_drawSprite(c->window, c->p_menu.exit, NULL);
    sfRenderWindow_drawSprite(c->window, c->p_menu.main_menu, NULL);
    place_cursor(c);
}
