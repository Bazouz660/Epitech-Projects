/*
** EPITECH PROJECT, 2021
** MY_HUNTER_BST
** File description:
** set_ups2.c
*/

#include "../includes/my_hunter.h"

h_p text_set_up2(h_p h, char *highscore_str)
{
    sfText_setCharacterSize(h.speed_count_display, 30);
    sfText_setCharacterSize(h.score, 30);
    sfText_setFillColor(h.score, sfBlack);
    sfText_setFillColor(h.score_count_text, sfBlack);
    sfText_setFillColor(h.speed_display, sfBlack);
    sfText_setFillColor(h.highscore_text, sfBlack);
    sfText_setFillColor(h.highscore_text_value, sfBlack);
    sfText_setFillColor(h.speed_count_display, sfBlack);
    sfText_setPosition(h.score_count_text, h.score_count_pos);
    sfText_setPosition(h.score, h.score_pos);
    sfText_setPosition(h.highscore_text, h.highscore_text_pos);
    sfText_setPosition(h.highscore_text_value, h.highscore_text_value_pos);
    sfText_setPosition(h.speed_display, h.speed_display_pos);
    sfText_setPosition(h.speed_count_display, h.speed_count_pos);
    return h;
}


h_p initialize_vars1(h_p h)
{
    h.mouse_pos = sfMouse_getPositionRenderWindow(h.window);
    h.score = sfText_create();
    h.highscore_text = sfText_create();
    h.highscore_text_value = sfText_create();
    h.speed_display = sfText_create();
    h.speed_count_display = sfText_create();
    h.score_count_text = sfText_create();
    h.font = sfFont_createFromFile("misc/game_font.ttf");
    h.defeat = sfFalse;
    h.enemy_speed = 0;
    h.heli_health = 1;
    h.counter = 0;
    return h;
}

h_p initialize_sounds(h_p h)
{
    h.shot = set_up_new_sound(h.shot, "sounds/shot.wav");
    h.main_menu_music = set_up_new_sound(h.main_menu_music, "sounds/main_menu_music.wav");
    h.reload_sound = set_up_new_sound(h.reload_sound, "sounds/reload.wav");
    h.music = set_up_new_sound(h.music, "sounds/music.wav");
    h.ricochet_sound = set_up_new_sound(h.ricochet_sound, "sounds/ricochet.wav");
    h.reporter_sound = set_up_new_sound(h.reporter_sound, "sounds/reporter_death.wav");
    h.easter_egg_sound = set_up_new_sound(h.easter_egg_sound, "sounds/easter_egg.wav");
    h.explosion_sound = set_up_new_sound(h.explosion_sound, "sounds/explosion.wav");
    h.defeat_sound = set_up_new_sound(h.defeat_sound, "sounds/defeat.wav");
    return h;
}

h_p initialize_vars2(h_p h)
{
    h.angle = 0;
    h.textseq = 0;
    h.reload_time = 0;
    h.reloading = 0;
    h.score_count = 0;
    h.health_points = 5;
    h.health_spritesheet_offset = 4955;
    h.reporter_spritesheet_offset = 0;
    h.result = malloc(sizeof(char) * 1);
    h.result2 = malloc(sizeof(char) * 1);
    h.score_str = malloc(sizeof(char) * 5);
    h.speed_count_str = malloc(sizeof(char) * 5);
    h.speed_count_str = "0";
    h.score_str = "0";
    return h;
}

h_p initialize_all_h(h_p h, char *highscore_str)
{
    h = vectors2f_set_up(h);
    h = vectors2f_set_up2(h);
    h = sprites_set_up(h);
    h = initialize_sounds(h);
    h = initialize_vars1(h);
    h = initialize_vars2(h); 
    h = text_set_up(h, highscore_str);
    h = text_set_up2(h, highscore_str);
    h = initialize_other(h);
    h.main_menu_choice = 0;
    return h;
}