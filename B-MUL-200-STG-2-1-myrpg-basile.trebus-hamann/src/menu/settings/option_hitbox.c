/*
** EPITECH PROJECT, 2022
** sfsqfsqf
** File description:
** sqffsqf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void manage_exit_settings(core_t *c)
{
    c->option.leave_rect.left = 420;
    if ((sfMouse_isButtonPressed(sfMouseLeft)
        && get_mouse_intersect(c, c->option.leave_s) == 1)
        || sfKeyboard_isKeyPressed(sfKeyEscape)) {
        c->option.leave_rect.left = 840;
        c->bt_pressed = 8;
    } else if (get_mouse_intersect(c, c->option.leave_s) == 0)
        c->option.leave_rect.left = 0;
    sfSprite_setTextureRect(c->option.leave_s, c->option.leave_rect);
    sfRenderWindow_drawSprite(c->window, c->option.leave_s, NULL);
}

void manage_settings(core_t *c)
{
    manage_30fps(c);
    manage_60fps(c);
    manage_90fps(c);
    manage_120fps(c);
    manage_up(c);
    manage_down(c);
    manage_exit_settings(c);
    set_alpha_option(c);
    if (c->audio.volume < 0)
        c->audio.volume = 0;
    sfMusic_setVolume(c->audio.ambient_music, c->audio.volume);
    sfMusic_setVolume(c->audio.menu_music, c->audio.volume);
    sfSound_setVolume(c->audio.fall_atck_impact, c->audio.volume);
    sfSound_setVolume(c->audio.landing_sound, c->audio.volume);
    sfSound_setVolume(c->audio.roll_sound, c->audio.volume);
    sfSound_setVolume(c->audio.slash_sounds[0], c->audio.volume);
    sfSound_setVolume(c->audio.slash_sounds[1], c->audio.volume);
    sfSound_setVolume(c->audio.slash_sounds[2], c->audio.volume);
    sfSound_setVolume(c->audio.slash_sounds[3], c->audio.volume);
    sfSound_setVolume(c->audio.button_click, c->audio.volume);
}