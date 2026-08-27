/*
** EPITECH PROJECT, 2022
** sfqsfsqfsqfsqfsqf
** File description:
** qsffqsf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

sfBool get_mouse_intersect(core_t *c, sfSprite *to_check)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(c->window);
    int posX = sfSprite_getPosition(to_check).x;
    int posY = sfSprite_getPosition(to_check).y;
    int posX_offset = (sfSprite_getGlobalBounds(to_check).width + posX);
    int posY_offset = (sfSprite_getGlobalBounds(to_check).height + posY);

    if ((mouse_pos.x >= posX && mouse_pos.x <= posX_offset)
        && (mouse_pos.y >= posY && mouse_pos.y <= posY_offset))
        return sfTrue;
    else
        return sfFalse;
}

void manage_play(core_t *c)
{
    c->menu.button_rect[0].left = 420;
    if (sfMouse_isButtonPressed(sfMouseLeft) != 0 &&
        get_mouse_intersect(c, c->menu.button_s[0]) == 1) {
        c->menu.button_rect[0].left = 840;
        c->bt_pressed = 1;
    }
    else if (get_mouse_intersect(c, c->menu.button_s[0]) == 0) {
        c->menu.button_rect[0].left = 0;
        c->change_scene = 2;
        c->bt_pressed == 1 ? c->bt_pressed = 1 : 0;
    }
    sfSprite_setTextureRect(c->menu.button_s[0], c->menu.button_rect[0]);
    sfRenderWindow_drawSprite(c->window, c->menu.button_s[0], NULL);
}

void manage_option(core_t *c)
{
    c->menu.button_rect[1].left = 420;
    if (sfMouse_isButtonPressed(sfMouseLeft) != 0 &&
        get_mouse_intersect(c, c->menu.button_s[1]) == 1) {
        c->menu.button_rect[1].left = 840;
        c->bt_pressed = 2;
    }
    else if (get_mouse_intersect(c, c->menu.button_s[1]) == 0) {
        c->menu.button_rect[1].left = 0;
        c->change_scene = 1;
        c->bt_pressed == 2 ? c->bt_pressed = 2 : 0;
    }
    sfSprite_setTextureRect(c->menu.button_s[1], c->menu.button_rect[1]);
    sfRenderWindow_drawSprite(c->window, c->menu.button_s[1], NULL);
}

void manage_exit(core_t *c)
{
    c->menu.button_rect[2].left = 420;
    if (sfMouse_isButtonPressed(sfMouseLeft) != 0 &&
        get_mouse_intersect(c, c->menu.button_s[2]) == 1) {
        c->menu.button_rect[2].left = 840;
        c->bt_pressed = 3;
    } else if (get_mouse_intersect(c, c->menu.button_s[2]) == 0) {
        c->menu.button_rect[2].left = 0;
        c->bt_pressed == 3 ? c->bt_pressed = 3 : 0;
    }
    sfSprite_setTextureRect(c->menu.button_s[2], c->menu.button_rect[2]);
    sfRenderWindow_drawSprite(c->window, c->menu.button_s[2], NULL);
}

void manage_how_to_play(core_t *c)
{
    static int can_click = 1;
    sfIntRect rect = sfSprite_getTextureRect(c->menu.how_to_play_b);

    rect.left = 420;
    if (sfMouse_isButtonPressed(sfMouseLeft) != 0 &&
        get_mouse_intersect(c, c->menu.how_to_play_b) == 1 && can_click == 1) {
        rect.left = 840;
        can_click = 0;
        if (c->menu.how_to_play_open == True)
            c->menu.how_to_play_open = False;
        else
            c->menu.how_to_play_open = True;
    } else if (get_mouse_intersect(c, c->menu.how_to_play_b) == 0) {
        rect.left = 0;
    }
    if (!sfMouse_isButtonPressed(sfMouseLeft)
        && c->event.type == sfEvtMouseButtonReleased)
        can_click = 1;
    sfSprite_setTextureRect(c->menu.how_to_play_b, rect);
    sfRenderWindow_drawSprite(c->window, c->menu.how_to_play_b, NULL);
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        c->menu.how_to_play_open = False;
}

void manage_button(core_t *c)
{
    manage_play(c);
    manage_option(c);
    manage_exit(c);
    manage_how_to_play(c);
    if (c->event.type == sfEvtMouseButtonReleased && c->bt_pressed != 0) {
        c->scene_status = c->change_scene;
        if (c->scene_status == 1)
            load_save(c);
        sfSound_play(c->audio.button_click);
        if (c->bt_pressed == 3) {
            destroy_all(c);
            sfRenderWindow_close(c->window);
        }
        if (c->bt_pressed == 1) {
            sfMusic_stop(c->audio.menu_music);
            sfMusic_play(c->audio.ambient_music);
            c->color.fade_out.a = 255;
            c->menu.fade_out_curb = 0;
            c->menu.fade_out_time = 0;
            sfSprite_setColor(c->black_layer, c->color.fade_out);
        }
        c->bt_pressed = 0;
    }
}
