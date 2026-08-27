/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** manage_game_state.c
*/

#include "../includes/my_runner.h"

h_p manage_score(h_p h)
{
    h.score_count++;
    h.score_str = my_strcpy(h.score_str,
    int_to_string(h.score_str, h.score_count));
    sfText_setString(h.score_count_text, h.score_str);
    return h;
}

h_p manage_health(h_p h)
{
    static int temp_health = 5;

    if (temp_health > h.health_points) {
        sfSound_play(h.pain);
        h.health_spritesheet_offset += 222;
        h.health_bar = update_animated_sprite_v(h.health_bar,
        h.health_spritesheet_offset, 1280, 222);
        temp_health = h.health_points;
    }
    return h;
}
