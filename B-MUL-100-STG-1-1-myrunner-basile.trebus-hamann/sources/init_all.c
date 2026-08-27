/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** init_all.c
*/

#include "../includes/my_runner.h"

h_p init_all(h_p h, int argc, char ** argv)
{
    h = initialize_vars(h);
    h = textures_set_up(h);
    h = initialize_music(h);
    h = sounds_set_up(h);
    h = text_set_up(h);
    h = set_up_window(h);
    h = sprites_set_up(h);
    h = init_map(h, argc, argv);
    return h;
}

h_p initialize_music(h_p h)
{
    h.defeat_music = set_up_new_music(h.music, "sounds/defeat music.ogg");
    h.main_menu_music = set_up_new_music(h.music, "sounds/main_menu_music.ogg");
    h.music = set_up_new_music(h.music, "sounds/music.ogg");
    sfMusic_setVolume(h.defeat_music, 70);
    sfMusic_setLoop(h.music, sfTrue);
    sfMusic_setLoop(h.defeat_music, sfTrue);
    return h;
}
