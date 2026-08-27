/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** main_menu_handler.c
*/

#include "../includes/my_runner.h"

int main_menu_handler(h_p h)
{
    sfRenderWindow_drawSprite(h.window, h.main_menu, NULL);
    sfRenderWindow_display(h.window);
    sfMusic_play(h.main_menu_music);
    while (1) {
        sfRenderWindow_pollEvent(h.window, &h.event);
        h.mouse_pos = sfMouse_getPositionRenderWindow(h.window);
        if (h.mouse_pos.x >= 120 && h.mouse_pos.x <= 350
            && sfMouse_isButtonPressed(sfMouseLeft))
            if (h.mouse_pos.y >= 450 && h.mouse_pos.y <= 580)
                return 0;
            else if (h.mouse_pos.y >= 200 && h.mouse_pos.y <= 330)
                break;
    }
    sfMusic_stop(h.main_menu_music);
    sfMusic_play(h.music);
    sfRenderWindow_setMouseCursorVisible(h.window, sfFalse);
    return 1;
}
