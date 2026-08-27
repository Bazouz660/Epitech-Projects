/*
** EPITECH PROJECT, 2022
** fqsfsq
** File description:
** fsqfsq
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void destroy_music(core_t *c)
{
    sfMusic_stop(c->audio.ambient_music);
    sfMusic_destroy(c->audio.ambient_music);
    sfMusic_stop(c->audio.menu_music);
    sfMusic_destroy(c->audio.menu_music);
    sfSound_stop(c->audio.landing_sound);
    sfSound_destroy(c->audio.landing_sound);
    sfSound_stop(c->audio.fall_atck_impact);
    sfSound_destroy(c->audio.fall_atck_impact);
    sfSound_stop(c->audio.roll_sound);
    sfSound_destroy(c->audio.roll_sound);
    sfSound_stop(c->audio.button_click);
    sfSound_destroy(c->audio.button_click);
    sfSound_stop(c->audio.p_death);
    sfSound_destroy(c->audio.p_death);
}

void destroy_all(core_t *c)
{
    destroy_music(c);
}