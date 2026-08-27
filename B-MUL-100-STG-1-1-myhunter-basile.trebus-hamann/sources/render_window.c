/*
** EPITECH PROJECT, 2021
** csfml.c
** File description:
** TREBUS BASILE
*/
#include "../includes/my_hunter.h"

sfRenderWindow *create_window(char const *title)
{
    sfRenderWindow *Window;
    sfVideoMode mode = sfVideoMode_getDesktopMode();

    Window = sfRenderWindow_create(mode, title, sfFullscreen | sfClose, NULL);
    return (Window);
}

void display_cursor(h_p h)
{
    h.crosshair_pos.x = sfMouse_getPositionRenderWindow(h.window).x - 15;
    h.crosshair_pos.y = sfMouse_getPositionRenderWindow(h.window).y - 15;
    sfSprite_setPosition(h.crosshair, h.crosshair_pos);
    h.crosshair_pos.x = sfMouse_getPositionRenderWindow(h.window).x + 15;
    h.crosshair_pos.y = sfMouse_getPositionRenderWindow(h.window).y + 10;
    sfSprite_setPosition(h.reload_ico, h.crosshair_pos);
    h.crosshair_pos.x = sfMouse_getPositionRenderWindow(h.window).x - 20;
    h.crosshair_pos.y = sfMouse_getPositionRenderWindow(h.window).y - 55;
    sfSprite_setPosition(h.reload_key_ico, h.crosshair_pos);
}

void draw_background(h_p h)
{
    sfRenderWindow_drawSprite(h.window, h.background, sfFalse);
    sfRenderWindow_drawSprite(h.window, h.leZ_bg, sfFalse);
    sfRenderWindow_drawSprite(h.window, h.health_bar, sfFalse);
}

h_p refresh_image(h_p h)
{
    draw_background(h);
    sfText_setString(h.speed_count_display, h.speed_count_str);
    sfText_setString(h.score_count_text, h.score_str);
    sfRenderWindow_drawSprite(h.window, h.reporter2, sfFalse);
    sfRenderWindow_drawSprite(h.window, h.reporter, sfFalse);
    sfRenderWindow_drawSprite(h.window, h.heli, sfFalse);
    sfRenderWindow_drawSprite(h.window, h.leZ, sfFalse);
    sfRenderWindow_drawText(h.window, h.score, sfFalse);
    sfRenderWindow_drawText(h.window, h.highscore_text, sfFalse);
    sfRenderWindow_drawText(h.window, h.highscore_text_value, sfFalse);
    sfRenderWindow_drawText(h.window, h.speed_display, sfFalse);
    sfRenderWindow_drawText(h.window, h.speed_count_display, sfFalse);
    sfRenderWindow_drawText(h.window, h.score_count_text, sfFalse);
    sfRenderWindow_drawSprite(h.window, h.crosshair, sfFalse);
    display_cursor(h);
    return h;
}