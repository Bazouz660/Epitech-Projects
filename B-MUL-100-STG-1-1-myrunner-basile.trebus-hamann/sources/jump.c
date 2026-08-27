/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** jump.c
*/

#include "../includes/my_runner.h"

h_p jump_upward(h_p h)
{
    if (h.jumping == 1 && h.falling == 0) {
        if (h.jump_offset.y < 0) {
            if (h.u_col == 1)
                h.jump_offset.y = 0;
            h.jump_offset.y += 1;
            sfSprite_move(h.tank_man, h.jump_offset);
        } else {
            h.falling = 1;
            h.jumping = 0;
        }
    }
    return h;
}

h_p jump_fall(h_p h)
{
    if (h.falling == 1) {
        h.jump_offset.y = -25;
        h.jump_offset.x = 0;
        if (h.d_col == 0)
            h = apply_gravity(h);
        if (h.player_pos.y >= 800 || h.d_col == 1) {
            h.fall_offset.y = 0;
            h.falling = 0;
        }
    }
    if (h.falling == 1 || h.jumping == 1) {
        h.anim_speed_offset = -1;
    }
    return h;
}

h_p do_jump(h_p h)
{
    h = jump_upward(h);
    h = jump_fall(h);
    return h;
}

h_p apply_gravity(h_p h)
{
    if (h.player_pos.y <= 800) {
        h.fall_offset.y += 1;
        h.fall_offset.x = 0;
        sfSprite_move(h.tank_man, h.fall_offset);
    }
    return h;
}
