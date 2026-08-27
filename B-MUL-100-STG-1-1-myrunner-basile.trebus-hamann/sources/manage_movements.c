/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** manage_movements.c
*/

#include "../includes/my_runner.h"

h_p manage_D(h_p h)
{
    if (sfKeyboard_isKeyPressed(sfKeyD)
        && h.player_pos.x < 1800 && h.lock == 0
        && h.f_col == 0) {
        sfSprite_move(h.tank_man, h.speed_offset);
        h.anim_speed_offset = 0.04;
    }
    return h;
}

h_p manage_Q_CTRL(h_p h)
{
    if (sfKeyboard_isKeyPressed(sfKeyQ)
        && h.player_pos.x > 160 && h.lock == 0
        && h.b_col == 0) {
        sfSprite_move(h.tank_man, h.speed_offset2);
        h.anim_speed_offset = -0.04;
    } else if (sfKeyboard_isKeyPressed(sfKeyLControl) && h.timer <= 0
                && h.slide_cooldown == 0 && h.sliding == 0) {
        h.sliding = 1;
        h.timer = 10;
    }
    return h;
}

h_p manage_Space(h_p h)
{
    if (sfKeyboard_isKeyPressed(sfKeySpace)
        && h.jumping == 0 && h.falling == 0 && h.jump_lock == 0) {
        sfSprite_setTexture(h.tank_man, h.running_txt, sfFalse);
        h.lock = 0;
        h.timer = 0;
        h.sliding == 1 ? h.slide_cooldown = 1 : 0;
        h.sliding = 0;
        h.jumping = 1;
        h.falling = 0;
    }
    return h;
}
