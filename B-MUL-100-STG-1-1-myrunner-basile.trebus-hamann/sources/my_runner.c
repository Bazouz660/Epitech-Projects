/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** my_runner.c
*/

#include "../includes/my_runner.h"

int close_window(sfRenderWindow *window, sfEvent event)
{
    if (event.type == sfEvtClosed ||
    sfKeyboard_isKeyPressed(sfKeyEscape)) {
        return(1);
    }
    return 0;
}

h_p game_loop_2(h_p h)
{
    draw_hud(h);
    h = pause_handler(h);
    h = animate_character(h);
    h = animate_background(h);
    h = manage_health(h);
    return h;
}

h_p main_game_loop(h_p h)
{
    while (sfRenderWindow_isOpen(h.window)) {
        h.time = sfClock_getElapsedTime(h.clock);
        h.seconds = h.time.microseconds / 1000000.0;
        h.player_pos = sfSprite_getPosition(h.tank_man);
        draw_background(h);
        h = manage_score(h);
        h = manage_mines(h);
        h. blocks != 0 ? h = manage_blocks(h) : h;
        h = manage_events(h);
        sfRenderWindow_drawSprite(h.window, h.tank_man, NULL);
        h = game_loop_2(h);
        if (h.health_points <= 0 || h.player_pos.x < -40)
            h.exit = 1;
        if (h.exit == 1 || h.win == 1)
            return h;
        sfRenderWindow_display(h.window);
    }
    return h;
}

h_p manage_end_screen(h_p h, int ac, char **av)
{
    sfBool exit = 0;

    sfMusic_stop(h.music);
    if (h.win == 0) {
        sfRenderWindow_drawSprite(h.window, h.end_screen, NULL);
        sfRenderWindow_display(h.window);
        sfMusic_play(h.defeat_music);
    } else {
        sfRenderWindow_drawSprite(h.window, h.win_screen, NULL);
        sfRenderWindow_display(h.window);
        sfSound_play(h.win_sound);
    }
    while (exit != 1) {
        sfRenderWindow_pollEvent(h.window, &h.event);
        if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
            exit = 1;
        }
    }
    return h;
}

int main(int argc, char **argv)
{
    h_p h;
    int error = error_handler(argc, argv);

    if (error != 1)
        return error;
    h = init_all(h, argc, argv);
    if (main_menu_handler(h) == 0)
        return 0;
    h = main_game_loop(h);
    h = manage_end_screen(h, argc, argv);
    return 0;
}

