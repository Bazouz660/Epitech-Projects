/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** pause_handler.c
*/

#include "../includes/my_runner.h"

h_p manage_pause_menu(h_p h)
{
    while (h.pause == 1) {
        if ((sfMouse_getPositionRenderWindow(h.window).x >= 880
            && sfMouse_getPositionRenderWindow(h.window).x <= 1040)
            && (sfMouse_getPositionRenderWindow(h.window).y >= 500
            && sfMouse_getPositionRenderWindow(h.window).y <= 530))
            if (sfMouse_isButtonPressed(sfMouseLeft)) {
                sfRenderWindow_setMouseCursorVisible(h.window, sfFalse);
                sfMusic_play(h.music);
                h.pause = 0;
            }
        if ((sfMouse_getPositionRenderWindow(h.window).x >= 899
            && sfMouse_getPositionRenderWindow(h.window).x <= 1010)
            && (sfMouse_getPositionRenderWindow(h.window).y >= 587
            && sfMouse_getPositionRenderWindow(h.window).y <= 625)
            && sfMouse_isButtonPressed(sfMouseLeft)) {
            h.exit = 1;
            h.pause = 0;
        }
    }
    return h;
}

h_p pause_handler(h_p h)
{
    if (sfKeyboard_isKeyPressed(sfKeyP)) {
        sfRenderWindow_drawSprite(h.window, h.p_menu, NULL);
        sfRenderWindow_display(h.window);
        h.pause = 1;
        sfMusic_pause(h.music);
        sfRenderWindow_setMouseCursorVisible(h.window, sfTrue);
    }
    h = manage_pause_menu(h);
    return h;
}
