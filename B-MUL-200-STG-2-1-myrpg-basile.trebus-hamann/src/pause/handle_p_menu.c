/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** handle_p_menu.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void manage_resume(core_t *c)
{
    sfSprite_setTextureRect(c->p_menu.resume, init_irect(420, 0, 420, 105));
    if (sfMouse_isButtonPressed(sfMouseLeft) &&
        get_mouse_intersect_view(c,
        sfSprite_getGlobalBounds(c->p_menu.resume)) == 1) {
        c->bt_pressed = 1;
        sfSprite_setTextureRect(c->p_menu.resume, init_irect(840, 0, 420, 105));
    } else if (get_mouse_intersect_view(c,
        sfSprite_getGlobalBounds(c->p_menu.resume)) == 0)
        sfSprite_setTextureRect(c->p_menu.resume, init_irect(0, 0, 420, 105));
}

static void manage_main_menu(core_t *c)
{
    sfSprite_setTextureRect(c->p_menu.main_menu, init_irect(420, 0, 420, 105));
    if (sfMouse_isButtonPressed(sfMouseLeft) &&
        get_mouse_intersect_view(c,
        sfSprite_getGlobalBounds(c->p_menu.main_menu)) == 1) {
        c->bt_pressed = 3;
        sfSprite_setTextureRect(c->p_menu.main_menu, init_irect(840, 0, 420,
        105));
    } else if (get_mouse_intersect_view(c,
        sfSprite_getGlobalBounds(c->p_menu.main_menu)) == 0)
        sfSprite_setTextureRect(c->p_menu.main_menu, init_irect(0, 0, 420,
        105));
}

static void manage_exit(core_t *c)
{
    sfSprite_setTextureRect(c->p_menu.exit, init_irect(420, 0, 420, 105));
    if (sfMouse_isButtonPressed(sfMouseLeft) &&
        get_mouse_intersect_view(c,
        sfSprite_getGlobalBounds(c->p_menu.exit)) == 1) {
        c->bt_pressed = 4;
        sfSprite_setTextureRect(c->p_menu.exit, init_irect(840, 0, 420,
        105));
    } else if (get_mouse_intersect_view(c,
        sfSprite_getGlobalBounds(c->p_menu.exit)) == 0)
        sfSprite_setTextureRect(c->p_menu.exit, init_irect(0, 0, 420,
        105));
}

void go_to_menu(core_t *c)
{
    sfVector2f pos;
    sfVector2f pos2 = {0, 0};

    pos.x = sfRenderWindow_getSize(c->window).x / 2;
    pos.y = sfRenderWindow_getSize(c->window).y / 2;
    sfMusic_stop(c->audio.ambient_music);
    sfMusic_play(c->audio.menu_music);
    sfView_setCenter(c->view, pos);
    sfRenderWindow_setView(c->window, c->view);
    pos2.x = view_bounds(c->view).left;
    pos2.y = view_bounds(c->view).top;
    sfSprite_setPosition(c->black_layer, pos2);
    sfSprite_setColor(c->black_layer, sfBlack);
    c->scene_status = 0;
    c->color.fade_out.a = 255;
    c->menu.fade_out_curb = 0;
}

void handle_p_menu(core_t *c)
{
    manage_resume(c);
    manage_main_menu(c);
    manage_exit(c);
    if (c->event.type == sfEvtMouseButtonReleased
        && !sfMouse_isButtonPressed(sfMouseLeft)) {
        if (c->bt_pressed == 1)
            c->paused = 0;
        if (c->bt_pressed == 2)
            0;
        if (c->bt_pressed == 3) {
            c->paused = 0;
            go_to_menu(c);
        }
        if (c->bt_pressed == 4)
            sfRenderWindow_close(c->window);
        c->bt_pressed = 0;
    }
}
