/*
** EPITECH PROJECT, 2021
** MY_HUNTER_BST
** File description:
** sprite_handler.c
*/

#include "../includes/my_hunter.h"

h_p loop_sprite_pos_h(h_p h)
{
    if (h.reporterpos.x >= 1920) {
        h.health_points--;
        h.health_spritesheet_offset -= 991;
        update_animated_sprite(h.health_bar, h.health_spritesheet_offset, 991, 397);
        h.reporterpos.x = -100;
    }
    if (h.reporterpos2.x >= 1920) {
        h.health_spritesheet_offset -= 991;
        update_animated_sprite(h.health_bar, h.health_spritesheet_offset, 991, 397);
        h.health_points--;
        h.reporterpos2.x = -150;
    }
    if (h.heli_pos.x >= 1920) {
        h.heli_health = 1;
        h.health_spritesheet_offset -= 991;
        update_animated_sprite(h.health_bar, h.health_spritesheet_offset, 991, 397);
        h.health_points--;
        h.heli_pos.x = -300;
    }
    return h;
}

h_p sprites_position_updater(h_p h)
{
    h.heli_pos.x  = h.heli_pos.x + h.enemy_speed + random_number(20, 30);
    h.reporterpos.x  = h.reporterpos.x + h.enemy_speed + random_number(10, 25);
    h.reporterpos2.x = h.reporterpos2.x + h.enemy_speed + random_number(10, 20);
    sfSprite_setPosition(h.reporter2, h.reporterpos2);
    sfSprite_setPosition(h.reporter, h.reporterpos);
    sfSprite_setPosition(h.heli, h.heli_pos);
    return h;
}

h_p sprites_texture_update_handler(h_p h)
{
    if (h.textseq == 0) {
        update_animated_sprite(h.reporter, 0, 122, 124);
        update_animated_sprite(h.reporter2, 0, 122, 124);
        if (h.heli_health < 1)
            update_animated_sprite(h.heli, 629 * 2, 629, 2524);
        else
            update_animated_sprite(h.heli, 0, 629, 2524);
        h.textseq = 1;
    } else if (h.textseq == 1) {
        update_animated_sprite(h.reporter, 134, 122, 124);
        update_animated_sprite(h.reporter2, 134, 122, 124);
        if (h.heli_health < 1)
            update_animated_sprite(h.heli, 629 * 3, 629, 2524);
        else
            update_animated_sprite(h.heli, 629, 629, 2524);
        h.textseq = 0;
    }
    return h;
}

h_p animations_handler(h_p h)
{
    if (h.seconds >= 0.15) {
        h = reload_time_handler(h);
        h = sprites_position_updater(h);
        h = sprites_texture_update_handler(h);
        h.counter++;
        sfClock_restart(h.clock);
    }
    return h;
}