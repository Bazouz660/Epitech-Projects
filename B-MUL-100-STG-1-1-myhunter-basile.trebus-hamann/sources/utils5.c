/*
** EPITECH PROJECT, 2021
** MY_HUNTER_BST
** File description:
** utils5.c
*/

#include "../includes/my_hunter.h"

h_p reload_time_handler(h_p h)
{
    if (h.reloading == 1)
            h.reload_time += -15;
        if (h.reload_time <= 0) {
            h.reload_time = 0;
            h.reloading = 0;
        }
    return h;
}

h_p difficulty_adapter(h_p h)
{
    if (h.counter >= 20 && h.enemy_speed < 45) {
        h.enemy_speed++;
        h.speed_count_str = (int_to_string(h.result2, h.enemy_speed));
        h.counter = 0;
    }
    return h;
}

h_p rotate_reload_ico(h_p h)
{
    if (h.seconds >= 0.05) {
        h.angle += 10;
        sfSprite_setRotation(h.reload_ico, h.angle);
    }
    return h;
}

h_p check_for_defeat(h_p h)
{
    if (h.health_points == 0) {
        update_animated_sprite(h.health_bar, h.health_spritesheet_offset - 991, 991, 950);
        h.defeat = sfTrue;
    }
    return h;
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i = i + 1;
    if (s1[i] < s2[i] || s1[i] == '\0' && s1[i] != s2[i])
        return (-1);
    else if (s1[i] > s2[i] || s2[i] == '\0' && s1[i] != s2[i])
        return (1);
    else
        return (0);
}