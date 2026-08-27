/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** my_runner.h
*/

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

typedef struct mine_list
{
    sfSprite *mine;
    sfVector2f mine_pos;
    int animation_pos;
    int exploded;
    struct mine_list *next;
} mine_list_t;

typedef struct mine_list_body {
    mine_list_t *start;
    mine_list_t *end;
    mine_list_t *temp_data;
} m_b;

typedef struct block_list
{
    sfSprite *block;
    sfVector2f block_pos;
    int animation_pos;
    int deleted;
    struct block_list *next;
} block_list_t;

typedef struct block_list_body {
    block_list_t *start;
    block_list_t *end;
    block_list_t *temp_data;
} b_b;

typedef struct init_map_package {
    char *buff;
    int fd;
    int entities;
    int type;
    int offset_b;
    int offset_m;
    char **map_array;
    int lines;
    int x;
    int mem;
    int w;
    sfVector2i entity_pos;
} map;

typedef struct hunter_package {
    FILE *fp;
    sfRenderWindow *window;
    sfEvent event;
    sfMusic *music;
    sfMusic *main_menu_music;
    sfMusic *defeat_music;
    sfSound *pain;
    sfSound *win_sound;
    sfSound *explosion;
    sfSound *explosion_sound;
    sfSound *defeat_sound;
    sfSprite *background;
    sfSprite *hud;
    sfSprite *tank_man;
    sfSprite *end_screen;
    sfSprite *main_menu;
    sfSprite *road_layer;
    sfSprite *tanks_layer;
    sfSprite *sky_layer;
    sfSprite *city_layer;
    sfSprite *lights_layer;
    sfSprite *p_menu;
    sfSprite *xina;
    sfSprite *end_text;
    sfSprite *exit_text;
    sfSprite *health_bar;
    sfSprite *win_screen;
    sfVector2f speed_offset;
    sfVector2f speed_offset2;
    sfVector2f slide_speed;
    sfVector2f jump_offset;
    sfVector2f fall_offset;
    sfVector2f exit_text_pos;
    sfVector2f health_bar_pos;
    sfVector2f tank_man_pos;
    sfVector2f xina_pos;
    sfVector2f p_menu_pos;
    sfVector2f health_bar_rect;
    sfVector2f crosshair_pos;
    sfVector2f player_pos;
    sfVector2f score_count_pos;
    sfVector2f speed_display_pos;
    sfVector2f speed_count_pos;
    sfVector2i mouse_pos;
    sfTexture *gunshot_text_blank;
    sfTexture *gunshot_texture;
    sfTexture *sliding_txt;
    sfTexture *running_txt;
    sfTexture *idling0_txt;
    sfTexture *idling1_txt;
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
    sfVector2f block_offset;
    sfVector2f fix ;
    sfVector2f reset_pos;
    int lock;
    int timer;
    int jump_lock;
    int height;
    int jumping;
    int falling;
    int idling;
    float anim_speed_offset;
    int counter;
    int x;
    int ground;
    int mines;
    int blocks;
    int main_menu_choice;
    int exit;
    int explosion_offset;
    int y;
    int pause;
    int x2;
    int y2;
    int angle;
    int textseq;
    int sliding;
    int reloading;
    int score_count;
    int slide_cooldown;
    int win;
    int health_points;
    int health_spritesheet_offset;
    int reporter_spritesheet_offset;
    float seconds;
    int f_col;
    int b_col;
    int u_col;
    int d_col;
    int standing;
    float r_explosion;
    float r_1;
    float r_2;
    float r_3;
    float r_4;
    float r_5;
    float r_6;
    float r_7;
    char *result;
    char *result2;
    char *score_str;
    char *speed_count_str;
    mine_list_t *m_list;
    m_b m_b;
    block_list_t *b_list;
    b_b b_b;
    map map;
} h_p;

sfRenderWindow *create_window(char const *title);
char *my_strcpy(char *dest, char const *src);
char *my_revstr(char *str);
char *int_to_string(char *str, int nb);
int my_strlen(char const *str);
int random_int(int n);
float random_number(int min_num, int max_num);
int	my_atoi(char *str);
int get_int_len(int nb);
int my_strcmp(char const *s1, char const *s2);
h_p initialize_vars(h_p h);
h_p initialize_vars2(h_p h);
h_p initialize_vars3(h_p h);
h_p initialize_vars4(h_p h);
h_p initialize_vars5(h_p h);
h_p init_all(h_p h, int argc, char ** argv);
h_p initialize_music(h_p h);
h_p textures_set_up(h_p h);
h_p initialize_music(h_p h);
h_p textures_set_up(h_p h);
h_p sounds_set_up(h_p h);
h_p text_set_up(h_p h);
h_p set_up_window(h_p h);
h_p sprites_set_up(h_p h);
h_p init_map(h_p h, int argc, char **argv);
sfMusic *set_up_new_music(sfMusic *new_music, const char *buffer_location);
sfSound *set_up_new_sound(sfSound *new_sound, const char *buffer_location);
h_p check_collision(h_p h, sfVector2f block_pos);
h_p check_for_u_col(h_p h, sfVector2f block_pos);
h_p check_for_b_col(h_p h, sfVector2f block_pos);
h_p check_for_f_col(h_p h, sfVector2f block_pos);
h_p check_for_d_col(h_p h, sfVector2f block_pos);
h_p can_get_up(h_p h, sfVector2f block_pos);
h_p is_idling(h_p h);
h_p init_map(h_p h, int ac, char **av);
map set_array_memory(map m, int j);
map add_to_game(map m, int j);
map init_map_vars(map m, char **av);
h_p add_block_to_list(h_p h, int posX, int posY);
h_p sprites_set_up(h_p h);
h_p text_set_up(h_p h);
sfSprite *new_sprite_looping(char *texture_name, float x, float y);
sfSprite *new_sprite(char *texture_name, float x, float y);
sfSprite *update_animated_sprite(sfSprite *, int , int , int);
sfSprite *update_animated_sprite_v(sfSprite *, int , int , int);
sfSprite *new_sprite(char *texture_name, float x, float y);
sfSprite *new_sprite_looping(char *texture_name, float x, float y);
h_p set_sprites_pos(h_p h);
h_p do_slide(h_p h);
h_p slide_cooldown(h_p h);
h_p manage_Space(h_p h);
h_p manage_Q_CTRL(h_p h);
h_p manage_D(h_p h);
h_p jump_upward(h_p h);
h_p jump_fall(h_p h);
h_p do_jump(h_p h);
h_p apply_gravity(h_p h);
h_p pause_handler(h_p h);
h_p manage_pause_menu(h_p h);
h_p draw_or_delete_block(h_p h, sfVector2f block_pos);
h_p move_block(h_p h);
h_p manage_blocks(h_p h);
h_p animate_character(h_p h);
h_p animate_background(h_p h);
h_p manage_events(h_p h);
int close_window(sfRenderWindow *window, sfEvent event);
h_p add_mine_to_list(h_p h, int pos, int nb);
h_p manage_mines(h_p h);
h_p spawn_mines(h_p h);
void draw_hud(h_p h);
void draw_background(h_p h);
sfSprite *new_sprite_looping(char *texture_name, float x, float y);
sfSprite *new_sprite(char *texture_name, float x, float y);
h_p manage_health(h_p h);
h_p manage_score(h_p h);
int error_handler(int argc, char **argv);
void read_usage(void);
int main_menu_handler(h_p h);
