/*
** EPITECH PROJECT, 2021
** MY_HUNTER_BST
** File description:
** set_ups1.c
*/

#include "../includes/my_hunter.h"

sfSound *set_up_new_sound(sfSound *new_sound, const char *buffer_location)
{
    new_sound = sfSound_create();
    sfSoundBuffer *new_sound_buffer = sfSoundBuffer_createFromFile(buffer_location);
    sfSound_setBuffer(new_sound, new_sound_buffer);
    return (new_sound);
}

h_p sprites_set_up(h_p h)
{
    h.main_menu = new_sprite(h.window, "sprites/MainMenu.jpg", 1 , 1);
    h.background = new_sprite(h.window, "sprites/background.png", 1, 1);
    h.reload_key_ico = new_sprite(h.window, "sprites/reload_key_ico.png", 0.07, 0.07);
    h.gunshot = new_sprite(h.window, "sprites/gunshot.png", 0.3, 0.3);
    h.leZ = new_sprite(h.window, "sprites/mirador_foreground.png", 1, 1);
    h.leZ_bg = new_sprite(h.window, "sprites/mirador.png", 1, 1);
    h.explosion = new_sprite(h.window, "sprites/explosion.png", 0.6, 0.6);
    h.reload_ico = new_sprite(h.window, "sprites/reload.png", 0.035, 0.035);
    h.blood_splatter = new_sprite(h.window, "sprites/blood_splatter.png", 0.9, 0.9);
    h.crosshair = new_sprite(h.window, "sprites/crosshair.png", 0.025, 0.025);
    h.reporter = new_sprite(h.window, "sprites/reporter_spritesheet.png", 1.3, 1.3);
    h.end_text = new_sprite(h.window, "sprites/you_died.png", 3.2, 3.2);
    h.exit_text = new_sprite(h.window, "sprites/exit_text.png", 0.9, 0.9);
    h.reporter2 =  new_sprite(h.window, "sprites/reporter_spritesheet.png" , 1.3, 1.3);
    h.health_bar = new_sprite(h.window, "sprites/health_spritesheet.png", 0.3, 0.3);
    h.heli = new_sprite(h.window, "sprites/heli_spritesheet.png", 0.9, 0.9);
    return h;
}

h_p vectors2f_set_up(h_p h)
{
    h.end_text_pos.x = 0;
    h.end_text_pos.y = 420;
    h.highscore_text_pos.x = 5;
    h.highscore_text_pos.y = 50;
    h.highscore_text_value_pos.x = 245;
    h.highscore_text_value_pos.y = 50;
    h.score_pos.x = 5;
    h.exit_text_pos.x = 520;
    h.health_bar_pos.x = 1600;
    h.leZpos.x = 1500;
    h.reporterpos.x = 900;
    h.reporterpos2.x = 300;
    h.heli_pos.x = 0;
    h.heli_new_pos;
    h.reload_ico_origin.x = 250;
    h.explosion_origin.x = -280;
    h.crosshair_pos.x;
    h.score_count_pos.x = 155;
    h.speed_display_pos.x = 400;
    return h;
}

h_p vectors2f_set_up2(h_p h)
{
    h.speed_count_pos.x = 550;
    h.gunshot_pos.x = 1495;
    h.score_pos.y = 0;
    h.exit_text_pos.y = 670;
    h.health_bar_pos.y = 10;
    h.leZpos.y = 550;
    h.reporterpos.y = 900;
    h.reporterpos2.y = 900;
    h.heli_pos.y = 200;
    h.heli_new_pos;
    h.reload_ico_origin.y = 250;
    h.explosion_origin.y = 0;
    h.crosshair_pos.y;
    h.score_count_pos.y = 0;
    h.speed_display_pos.y = 0;
    h.speed_count_pos.y = 0;
    h.gunshot_pos.y = 620;
    return h;
}

h_p text_set_up(h_p h, char *highscore_str)
{
    sfText_setFont(h.score, h.font);
    sfText_setFont(h.highscore_text, h.font);
    sfText_setFont(h.highscore_text_value, h.font);
    sfText_setFont(h.score_count_text, h.font);
    sfText_setFont(h.speed_display, h.font);
    sfText_setFont(h.speed_count_display, h.font);
    sfText_setString(h.score, "Score: ");
    sfText_setString(h.highscore_text, "Highscore: ");
    sfText_setString(h.highscore_text_value, highscore_str);
    sfText_setString(h.score_count_text, h.score_str);
    sfText_setString(h.speed_display, "Speed: ");
    sfText_setString(h.speed_count_display, h.speed_count_str);
    sfText_setCharacterSize(h.score_count_text, 30);
    sfText_setCharacterSize(h.highscore_text, 30);
    sfText_setCharacterSize(h.highscore_text_value, 30);
    sfText_setCharacterSize(h.speed_display, 30);
    return h;
}