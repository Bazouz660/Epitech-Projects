/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** check_collisions.c
*/

#include "../includes/my_runner.h"

h_p check_for_d_col(h_p h, sfVector2f block_pos)
{
    if (h.player_pos.y > 191 && h.falling == 1) {
        h.fix.x = h.player_pos.x;
        h.fix.y = block_pos.y - 191;
        sfSprite_setPosition(h.tank_man, h.fix);
    }
    h.d_col = 1;
    h.falling = 0;
    h.fall_offset.y = 0;
    return h;
}

h_p check_for_f_col(h_p h, sfVector2f block_pos)
{
    if ((h.player_pos.x >= block_pos.x - 45
        && h.player_pos.x <= block_pos.x + 5)
        && (h.player_pos.y > block_pos.y - 190
        && h.player_pos.y < block_pos.y + 100)) {
            h.f_col = 1;
        if (h.sliding == 1 && h.player_pos.y > block_pos.y + 40)
            h.f_col = 0;
    } else
        h.f_col = 0;
    return h;
}

h_p check_for_b_col(h_p h, sfVector2f block_pos)
{
    if ((h.player_pos.x >= block_pos.x - 10
        && h.player_pos.x <= block_pos.x + 180)
        && ((h.player_pos.y > block_pos.y - 190)
        && (h.player_pos.y < (block_pos.y + 100)))) {
        h.b_col = 1;
    } else
        h.b_col = 0;
    return h;
}

h_p check_for_u_col(h_p h, sfVector2f block_pos)
{
    if ((h.player_pos.x >= block_pos.x - 30
        && h.player_pos.x <= block_pos.x + 180)
        && ((h.player_pos.y > block_pos.y - 190)
        && (h.player_pos.y < (block_pos.y + 105)))) {
        h.jumping = 0;
        h.u_col = 1;
    } else
        h.u_col = 0;
    return h;
}

h_p check_collision(h_p h, sfVector2f block_pos)
{
    h = is_idling(h);
    if ((h.player_pos.x >= block_pos.x - 35
        && h.player_pos.x <= block_pos.x + 180)
        && (h.player_pos.y >= block_pos.y - 191)
        && (h.player_pos.y < block_pos.y - 100)) {
        h = check_for_d_col(h, block_pos);
    } else {
        h.d_col = 0;
        h = check_for_f_col(h, block_pos);
        h = check_for_b_col(h, block_pos);
        h = check_for_u_col(h, block_pos);
        h = can_get_up(h, block_pos);
    }
    return h;
}
