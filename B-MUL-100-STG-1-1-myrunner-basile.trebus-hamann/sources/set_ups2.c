/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** set_ups2.c
*/

#include "../includes/my_runner.h"

h_p sprites_set_up(h_p h)
{
    h.tank_man = new_sprite_looping("sprites/running.png", 3, 3);
    h.city_layer = new_sprite_looping("sprites/city.png", 1, 1);
    h.tanks_layer = new_sprite_looping("sprites/tanks.png", 1, 1);
    h.sky_layer = new_sprite_looping("sprites/sky.png", 1, 1);
    h.lights_layer = new_sprite_looping("sprites/lights.png", 1, 1);
    h.road_layer = new_sprite_looping("sprites/road.png", 1, 1);
    h.health_bar = new_sprite("sprites/health_bar.png", 0.3, 0.3);
    h.win_screen = new_sprite("sprites/win_screen.jpg", 1, 1);
    h.main_menu = new_sprite("sprites/main_menu.jpg", 1, 1);
    h.hud = new_sprite("sprites/hud.png", 4.8, 4);
    h.end_screen = new_sprite("sprites/end screen.jpg", 2, 2);
    h.p_menu = new_sprite("sprites/pause.png", 4.8, 4);
    h.xina = new_sprite("sprites/xina.png", 0.25, 0.15);
    h.tank_man = update_animated_sprite(h.tank_man, 0, 64, 64);
    h.p_menu = update_animated_sprite(h.p_menu, 0, 76, 107);
    h.health_bar = update_animated_sprite(h.health_bar, 0, 1280, 222);
    h = set_sprites_pos(h);
    return h;
}

h_p text_set_up(h_p h)
{
    h.score_count_text = sfText_create();
    sfText_setFont(h.score_count_text, h.font);
    sfText_setString(h.score_count_text, "00000");
    sfText_setCharacterSize(h.score_count_text, 30);
    sfText_setFillColor(h.score_count_text, sfBlack);
    sfText_setPosition(h.score_count_text, h.score_count_pos);
    return h;
}

h_p set_sprites_pos(h_p h)
{
    sfVector2f tank_man_ori = {36, 0};
    sfVector2f pos = {450, 200};
    sfVector2f win_screen_pos = {710, 300};

    sfSprite_setPosition(h.end_screen, pos);
    sfSprite_setPosition(h.win_screen, win_screen_pos);
    sfSprite_setPosition(h.tank_man, h.tank_man_pos);
    sfSprite_setPosition(h.health_bar, h.health_bar_pos);
    sfSprite_setPosition(h.xina, h.xina_pos);
    sfSprite_setOrigin(h.tank_man, tank_man_ori);
    sfSprite_setPosition(h.p_menu, h.p_menu_pos);
    return h;
}
