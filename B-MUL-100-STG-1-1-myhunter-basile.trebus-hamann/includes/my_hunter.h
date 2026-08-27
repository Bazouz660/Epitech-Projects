/*
** EPITECH PROJECT, 2021
** my_hunter.h
** File description:
** hunter header
*/

#pragma once

#include "SFML/Graphics.h"
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct hunter_package {
    FILE *fp;
    sfRenderWindow *window;
    sfEvent event;
    sfSound *shot;
    sfSound *reload_sound;
    sfSound *main_menu_music;
    sfSound *music;
    sfSound *ricochet_sound;
    sfSound *reporter_sound;
    sfSound *easter_egg_sound;
    sfSound *explosion_sound;
    sfSound *defeat_sound;
    sfSprite *background;
    sfSprite *reload_key_ico;
    sfSprite *gunshot;
    sfSprite *leZ;
    sfSprite *main_menu;
    sfSprite *leZ_bg;
    sfSprite *explosion;
    sfSprite *reload_ico;
    sfSprite *blood_splatter;
    sfSprite *crosshair;
    sfSprite *reporter;
    sfSprite *end_text;
    sfSprite *exit_text;
    sfSprite *reporter2;
    sfSprite *health_bar;
    sfSprite *heli;
    sfVector2f end_text_pos;
    sfVector2f highscore_text_pos;
    sfVector2f highscore_text_value_pos;
    sfVector2f score_pos;
    sfVector2f exit_text_pos;
    sfVector2f health_bar_pos;
    sfVector2f leZpos;
    sfVector2f reporterpos;
    sfVector2f reporterpos2;
    sfVector2f heli_pos;
    sfVector2f heli_new_pos;
    sfVector2f reload_ico_origin;
    sfVector2f explosion_origin;
    sfVector2f crosshair_pos;
    sfVector2f score_count_pos;
    sfVector2f speed_display_pos;
    sfVector2f speed_count_pos;
    sfVector2f gunshot_pos;
    sfVector2i mouse_pos;
    sfTexture *gunshot_text_blank;
    sfTexture *gunshot_texture;
    sfTexture *heli_texture;
    sfTexture *heli_texture2;
    sfClock *clock;
    sfTime time;
    sfText *score;
    sfText *highscore_text;
    sfText *highscore_text_value;
    sfText *speed_display;
    sfText *speed_count_display;
    sfText *score_count_text;
    sfFont *font;
    sfBool defeat;
    int enemy_speed;
    int heli_health;
    int counter;
    int x;
    int main_menu_choice;
    int exit;
    int y;
    int x2;
    int y2;
    int angle;
    int textseq;
    int reload_time;
    int reloading;
    int score_count;
    int health_points;
    int health_spritesheet_offset;
    int reporter_spritesheet_offset;
    float seconds;
    char *result;
    char *result2;
    char *score_str;
    char *speed_count_str;
} h_p;

h_p refresh_image(h_p h);

void my_putchar(char c);

void initialize_music(h_p h);

sfSprite *update_animated_sprite(sfSprite *sprite, int offset, int width, int height);

void set_sprites_settings(h_p h);

int my_strcmp(char const *s1, char const *s2);

h_p initialize_other(h_p h);

h_p manage_reload(h_p h);

h_p reload_time_handler(h_p h);

h_p difficulty_adapter(h_p h);

h_p rotate_reload_ico(h_p h);

h_p check_for_defeat(h_p h);

h_p reload_time_handler(h_p h);

void display_defeat_screen(h_p h, int highscore);

int manage_defeat_screen(h_p h, int highscore, char *highscore_str);

int manage_click(sfMouseButtonEvent event, sfRenderWindow *window, int reload_time);

int close_window(sfRenderWindow *window, sfEvent event);

sfSprite *new_sprite(sfRenderWindow *window, char *texture_name, float, float);

char *fill_score(char *score, int score_count);

int random_number(int min_num, int max_num);

int hunter(int highscore, char *highscore_str);

int manage_click(sfMouseButtonEvent event, sfRenderWindow *window, int reload_time);

int close_window(sfRenderWindow *window, sfEvent event);

sfSprite *new_sprite(sfRenderWindow *window, char *texture_name, float x, float y);

sfRenderWindow *create_window(char const *title);

void my_putstr(char const *str);

int my_strlen(char const *str);

char *my_revstr(char *str);

int get_int_len(int nb);

char *int_to_string(char *str, int nb);

int my_getnbr(char const *str);

int my_put_nbr(int nb);

int my_strlen_num(char const *str);

sfSprite *update_animated_sprite(sfSprite *sprite, int offset, int width, int height);

char *fill_score(char *score, int score_count);

int random_number(int min_num, int max_num);

h_p manage_imputs(h_p h, sfEvent event);

h_p animations_handler(h_p h);

h_p loop_sprite_pos_h(h_p h);

h_p sprites_position_updater(h_p h);

h_p sprites_texture_update_handler(h_p h);

void display_cursor(h_p h);

h_p manage_hit1(h_p h);

h_p manage_events(h_p h);

h_p manage_hit2(h_p h);

h_p manage_hit3(h_p h);

void draw_background(h_p h);

h_p refresh_image(h_p h);

sfSound *set_up_new_sound(sfSound *new_sound, const char *buffer_location);

h_p sprites_set_up(h_p h);

h_p vectors2f_set_up(h_p h);

h_p vectors2f_set_up2(h_p h);

h_p text_set_up(h_p h, char *highscore_str);

h_p text_set_up2(h_p h, char *highscore_str);

h_p initialize_vars1(h_p h);

h_p initialize_sounds(h_p h);

h_p initialize_vars2(h_p h);

h_p initialize_all_h(h_p h, char *highscore_str);