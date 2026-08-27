/*
** EPITECH PROJECT, 2022
** zsqfsfsqfsqf
** File description:
** sqfsqfsqf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void place_cursor(core_t *c)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(c->window);
    sfVector2f cursor_pos = {mouse_pos.x + view_bounds(c->view).left,
    mouse_pos.y + view_bounds(c->view).top};

    sfSprite_setPosition(c->menu.cursor_s, cursor_pos);
    sfRenderWindow_drawSprite(c->window, c->menu.cursor_s, NULL);
}

void draw_menu(core_t *c)
{
    sfRenderWindow_drawSprite(c->window, c->menu.bg_1, NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.embers, NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.bg_2, NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.bg_4, NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.bg_3, NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.button_s[0], NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.button_s[1], NULL);
    sfRenderWindow_drawSprite(c->window, c->menu.button_s[2], NULL);
    manage_button(c);
    if (c->menu.how_to_play_open == True)
        sfRenderWindow_drawSprite(c->window, c->menu.how_to_play_sp, NULL);
    place_cursor(c);
    sfRenderWindow_drawSprite(c->window, c->black_layer, NULL);
}

void move_parallax_menu(core_t *c)
{
    sfVector2i mpos = sfMouse_getPositionRenderWindow(c->window);
    sfVector2f pos = {-((float)mpos.x / 30.1), 0};

    sfSprite_setPosition(c->menu.embers, pos);
    pos.x *= -1;
    pos.x /= 3;
    pos.y *= -1;
    pos.y /= 3;
    sfSprite_setPosition(c->menu.bg_2, pos);
    pos.x *= -1;
    pos.x /= 2;
    pos.y *= -1;
    pos.y /= 2;
    sfSprite_setPosition(c->menu.bg_4, pos);
}

void render_menu(core_t *c)
{
    update_clock(c);
    sfSprite_setPosition(c->black_layer,
    init_fvect(view_bounds(c->view).left - 300,
    view_bounds(c->view).top));
    fade_out(c, 0.05, 0.01, c->black_layer);
    move_parallax_menu(c);
    draw_menu(c);
}
