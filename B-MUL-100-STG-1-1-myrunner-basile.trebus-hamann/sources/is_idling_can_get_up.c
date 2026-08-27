/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** is_idling_can_get_up.c
*/

#include "../includes/my_runner.h"

h_p is_idling(h_p h)
{
    if (h.f_col == 1) {
        if (h.d_col == 1 || h.player_pos.y >= 800) {
            sfSprite_setTexture(h.tank_man, h.idling0_txt, sfFalse);
        } else
            sfSprite_setTexture(h.tank_man, h.running_txt, sfFalse);
        sfSprite_move(h.tank_man, h.block_offset);
    }
    return h;
}

h_p can_get_up(h_p h, sfVector2f block_pos)
{
    if ((h.player_pos.x >= block_pos.x - 20
        && h.player_pos.x <= block_pos.x + 140)
        && (block_pos.y + 30 < h.player_pos.y)
        && (h.player_pos.y - block_pos.y <= 90)
        && h.falling == 0 && h.jumping == 0
        && (h.d_col == 1 || h.player_pos.y >= 800)) {
        h.sliding = 1;
        h.jump_lock = 1;
        h.timer <= 1 ? h.timer = 2 : 0;
    } else
        h.jump_lock = 0;
    return h;
}
