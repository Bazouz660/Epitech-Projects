/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** create_render_window.c
*/

#include "../includes/my_runner.h"

sfRenderWindow *create_window(char const *title)
{
    sfRenderWindow *Window;
    sfVideoMode mode = sfVideoMode_getDesktopMode();

    Window = sfRenderWindow_create(mode, title, sfFullscreen | sfClose, NULL);
    return (Window);
}