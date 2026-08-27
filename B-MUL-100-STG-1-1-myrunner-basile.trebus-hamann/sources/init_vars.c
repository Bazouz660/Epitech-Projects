/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** init_vars.c
*/

#include "../includes/my_runner.h"

h_p initialize_vars_2(h_p h)
{
    h.slide_speed.x = 10;
    h.slide_speed.y = 0;
    h.slide_cooldown = 0;
    h.sliding = 0;
    h.exit = 0;
    h.standing = 0;
    h.timer = 0;
    h.xina_pos.x = 1670;
    h.xina_pos.y = 10;
    h.health_bar_pos.x = 390;
    h.health_bar_pos.y = 10;
    h.score_count = 0;
    h.score_count_pos.x = 400;
    h.score_count_pos.y = 113;
    h.health_spritesheet_offset = 0;
    h.font = sfFont_createFromFile("misc/font.ttf");
    h.explosion_offset = 0;
    h.tank_man_pos.x = 160;
    h.tank_man_pos.y = 800;
    return h;
}

h_p initialize_vars_3(h_p h)
{
    h.anim_speed_offset = 0;
    h.block_offset.x = -3;
    h.block_offset.y = 0;
    h.fix.x = 0;
    h.fix.y = 0;
    h.reset_pos.x = 2200;
    h.reset_pos.y = 750;
    h.speed_offset2.x = -6;
    h.speed_offset2.y = 0;
    h.jump_offset.y = -25;
    h.jump_offset.x = 0;
    h.f_col = 0;
    h.b_col = 0;
    h.u_col = 0;
    h.d_col = 0;
    return h;
}

h_p initialize_vars_4(h_p h)
{
    h.fall_offset.y = 0;
    h.mines = 0;
    h.idling = 0;
    h.p_menu_pos.x = 775;
    h.p_menu_pos.y = 300;
    h.health_points = 5;
    h.jump_lock = 0;
    h.height = 0;
    h.lock = 0;
    h.jumping = 0;
    h.pause = 0;
    h.falling = 0;
    h.mines = 0;
    h.blocks = 0;
    h.r_2 = 0;
    return h;
}

h_p initialize_vars_5(h_p h)
{
    h.m_b.start = NULL;
    h.m_b.end = NULL;
    h.b_b.start = NULL;
    h.b_b.end = NULL;
    h.m_list = NULL;
    h.b_list = NULL;
    h.r_1 = 0;
    h.r_2 = 0;
    h.r_3 = 0;
    h.r_4 = 0;
    h.r_5 = 0;
    h.r_6 = 0;
    h.r_7 = 0;
    h.win = 0;
    return h;
}

h_p initialize_vars(h_p h)
{
    h.score_str = malloc(sizeof(char) * 5);
    h.score_str = my_strcpy(h.score_str, "0000");
    h.speed_offset.x = 5;
    h.speed_offset.y = 0;
    h.exit = 0;
    h.r_explosion = 0;
    h = initialize_vars_2(h);
    h = initialize_vars_3(h);
    h = initialize_vars_4(h);
    h = initialize_vars_5(h);
    return h;
}
