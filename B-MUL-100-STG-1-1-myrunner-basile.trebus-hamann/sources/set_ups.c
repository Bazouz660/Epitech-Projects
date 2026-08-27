/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** set_ups.c
*/

#include "../includes/my_runner.h"

h_p set_up_window(h_p h)
{
    h.clock = sfClock_create();
    h.window = create_window("My Runner");
    sfRenderWindow_setKeyRepeatEnabled(h.window, sfTrue);
    sfRenderWindow_setFramerateLimit(h.window, 60);
    sfRenderWindow_setVerticalSyncEnabled(h.window, sfTrue);
    return h;
}

h_p sounds_set_up(h_p h)
{
    h.pain = set_up_new_sound(h.pain, "sounds/pain.ogg");
    h.win_sound = set_up_new_sound(h.win_sound, "sounds/win.ogg");
    h.explosion = set_up_new_sound(h.explosion, "sounds/explosion.ogg");
    sfSound_setVolume(h.pain, 20);
    return h;
}

sfSound *set_up_new_sound(sfSound *new_sound, const char *buffer_location)
{
    new_sound = sfSound_create();
    sfSoundBuffer *new_buffer = sfSoundBuffer_createFromFile(buffer_location);
    sfSound_setBuffer(new_sound, new_buffer);
    return (new_sound);
}

sfMusic *set_up_new_music(sfMusic *new_music, const char *buffer_location)
{
    new_music = sfMusic_createFromFile(buffer_location);
    return (new_music);
}

h_p textures_set_up(h_p h)
{
    h.sliding_txt = sfTexture_createFromFile("sprites/slide.png", NULL);
    h.running_txt = sfTexture_createFromFile("sprites/running.png", NULL);
    h.idling0_txt = sfTexture_createFromFile("sprites/tank_man_idle0.png", NULL);
    h.idling1_txt = sfTexture_createFromFile("sprites/tank_man_idle1.png", NULL);
    sfTexture_setRepeated(h.idling0_txt, sfTrue);
    sfTexture_setRepeated(h.idling1_txt, sfTrue);
    sfTexture_setRepeated(h.running_txt, sfTrue);
    sfTexture_setRepeated(h.sliding_txt, sfTrue);
    return h;
}
