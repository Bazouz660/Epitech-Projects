/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** handle_stats_upgrade.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void move_plus(core_t *c)
{
    sfVector2f ipos = sfSprite_getPosition(c->inventory.book_s);
    sfVector2f pos = {ipos.x + 265, ipos.y + 538};

    sfSprite_setPosition(c->inventory.plus_1, pos);
    pos.y += 23;
    sfSprite_setPosition(c->inventory.plus_2, pos);
    pos.y += 22;
    sfSprite_setPosition(c->inventory.plus_3, pos);
    pos.y += 22;
    sfSprite_setPosition(c->inventory.plus_4, pos);
    sfRenderWindow_drawSprite(c->window, c->inventory.plus_1, NULL);
    sfRenderWindow_drawSprite(c->window, c->inventory.plus_2, NULL);
    sfRenderWindow_drawSprite(c->window, c->inventory.plus_3, NULL);
    sfRenderWindow_drawSprite(c->window, c->inventory.plus_4, NULL);
}

static void handle_plus_2(core_t *c, int *selected)
{
    if (get_mouse_intersect_view(c,
        sfSprite_getGlobalBounds(c->inventory.plus_2))) {
        *selected = 2;
        sfSprite_setScale(c->inventory.plus_2, init_fvect(0.23, 0.23));
    } else
        sfSprite_setScale(c->inventory.plus_2, init_fvect(0.22, 0.22));
    if (get_mouse_intersect_view(c,
        sfSprite_getGlobalBounds(c->inventory.plus_3))) {
        *selected = 3;
        sfSprite_setScale(c->inventory.plus_3, init_fvect(0.23, 0.23));
    } else
        sfSprite_setScale(c->inventory.plus_3, init_fvect(0.22, 0.22));
    if (get_mouse_intersect_view(c,
        sfSprite_getGlobalBounds(c->inventory.plus_4))) {
        sfSprite_setScale(c->inventory.plus_4, init_fvect(0.23, 0.23));
        *selected = 4;
    } else
        sfSprite_setScale(c->inventory.plus_4, init_fvect(0.22, 0.22));
}

static void handle_stats_upgrade(core_t *c, int selected)
{
    if (selected == 1) {
        c->p.points--;
        c->p.vigor++;
    }
    if (selected == 2) {
        c->p.points--;
        c->p.stam_inv++;
    }
    if (selected == 3) {
        c->p.points--;
        c->p.strength++;
    }
    if (selected == 4) {
        c->p.points--;
        c->p.agility++;
    }
}

void handle_plus(core_t *c)
{
    int selected = 0;
    static int can_click = 1;

    if (get_mouse_intersect_view(c,
        sfSprite_getGlobalBounds(c->inventory.plus_1))) {
        sfSprite_setScale(c->inventory.plus_1, init_fvect(0.23, 0.23));
        selected = 1;
    } else
        sfSprite_setScale(c->inventory.plus_1, init_fvect(0.22, 0.22));
    handle_plus_2(c, &selected);
    if (sfMouse_isButtonPressed(sfMouseLeft) && can_click == 1) {
        can_click = 0;
        handle_stats_upgrade(c, selected);
    } else if (c->event.type == sfEvtMouseButtonReleased)
        can_click = 1;
}
