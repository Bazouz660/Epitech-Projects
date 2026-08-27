/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** events.c
*/

#include "../includes/my_runner.h"

h_p manage_imputs(h_p h)
{
    h.anim_speed_offset = 0;
    h.ground = 800;
    h = manage_D(h);
    h = manage_Q_CTRL(h);
    h = manage_Space(h);
    h = do_jump(h);
    h = do_slide(h);
    h = slide_cooldown(h);
    if (close_window(h.window, h.event) == 1) {
        h.exit = 1;
        h.win = 0;
    }
    return h;
}

h_p manage_events(h_p h)
{
    sfRenderWindow_pollEvent(h.window, &h.event);
    h = manage_imputs(h);
    return h;
}
