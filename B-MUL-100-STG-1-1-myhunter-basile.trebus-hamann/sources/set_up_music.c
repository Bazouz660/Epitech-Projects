/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myhunter-basile.trebus-hamann
** File description:
** set_up_music.c
*/

#include "../includes/my_hunter.h"

void initialize_music(h_p h)
{
    sfSound_stop(h.main_menu_music);
    sfRenderWindow_setMouseCursorVisible(h.window, sfFalse);
    sfSound_play(h.music);
    sfSound_setVolume(h.music, 70);
    sfSound_setLoop(h.music, sfTrue);
}