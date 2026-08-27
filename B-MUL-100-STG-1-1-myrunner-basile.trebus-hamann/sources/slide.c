/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** slide.c
*/

#include "../includes/my_runner.h"

h_p do_slide(h_p h)
{
    static int once = 0;

    if (h.sliding == 1) {
        sfSprite_setTexture(h.tank_man, h.sliding_txt, sfFalse);
        if (h.timer > 0
            && h.player_pos.x < 1800 && h.f_col == 0)
            sfSprite_move(h.tank_man, h.slide_speed);
        if (((h.seconds - h.r_2) >= 0.1) && h.timer > 0) {
            h.timer--;
            h.r_2 = h.seconds;
        }
        h.lock = 1;
        if ((h.timer <= 0 && h.b_col == 0)) { 
            sfSprite_setTexture(h.tank_man, h.running_txt, sfFalse);
            h.sliding = 0;
            h.lock = 0;
            h.slide_cooldown = 1;
            once = 0;
        }
    }
    return h;
}

h_p slide_cooldown(h_p h)
{
    if (h.slide_cooldown == 1)
        if (h.seconds - h.r_5 >= 2) {
            h.slide_cooldown = 0;
            h.r_5 = h.seconds;
        }
    return h;
}
