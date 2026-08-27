/*
** EPITECH PROJECT, 2021
** tower defense
** File description:
** towerdefense.h
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

typedef struct enemy_s_p {
    sfVector2f pos;
    int type;
} enemy_s_p;

typedef struct health_bar {
    sfRectangleShape *red_bar;
    sfRectangleShape *green_bar;
    sfVector2f hb_pos;
    sfVector2f hb_origin;
} health_bar;

typedef struct entity {
    float health;
    float health_mem;
    float health_mem2;
    float health_diff;
    int effect;
    int status;
    float speed;
    float speed_mem;
    float death_delay;
    int dmg;
    int type;
    float anim;
    float anim_spd;
    int reward;
    int weakness;
    int exploding;
    int explodion_frame;
    float expl_cooldown;
    sfBool mirrored;
    sfVector2f spd_vect;
    sfVector2f pos;
    sfSprite *sprite;
    sfSprite *effect_sprite;
    sfSprite *weakness_sprite;
    sfSprite *projectile;
    health_bar hb;
} entity;

typedef struct wave {
    struct entity enemy;
    struct wave *next;
    struct wave *prev;
    int index;
} wave;

typedef struct case_con {
    int u;
    int d;
    int r;
    int l;
} case_con;

typedef struct tower {
    int type;
    float sound_delay;
    float dmg;
    int effect;
    float atck_spd;
    float anim_spd;
    int ready;
    int range;
    int level;
    int cost;
    int up_cost;
    int frames;
    float atck_delay;
    sfTexture *texture;
} tower;

typedef struct grid_case {
    int type;
    sfSprite *entry;
    sfVector2f size;
    sfRectangleShape *unit;
    sfVector2f rect_pos;
    case_con cc;
    int entry_point;
    float anim_spd;
    tower tw;
} grid_rect;

typedef struct big_struct_full_of_fard {
    sfRenderWindow *window;
    sfEvent event;
    sfVector2u window_size;
    sfVector2i window_pos;
    sfVector2f mogus_scale;
    sfVector2f mogus_origin;
    sfVector2f mog_pos;
    sfVector2f mogus_hitbox_origin;
    sfVector2f mogus_hitbox_hint_size;
    sfVector2f mogus_offset;
    sfVector2f mouse_posF;
    sfVector2f vol_bar_scale;
    sfVector2u window_dim;
    sfVector2i mouse_pos;
    sfFloatRect mogus_box;
    sfSprite *mogus;
    sfSprite *build_menu_1;
    sfText *build_txt_1;
    sfSprite *build_menu_2;
    sfText *build_txt_2;
    sfSprite *build_menu_3;
    sfText *build_txt_3;
    sfSprite *build_menu_4;
    sfText *build_txt_4;
    sfSprite *upgrade_menu_1;
    sfText *upgrade_txt_1;
    sfSprite *upgrade_menu_2;
    sfText *upgrade_txt_2;
    sfSprite *heart;
    sfSprite *intro;
    sfSprite *background;
    sfSprite *background2;
    sfSprite *background3;
    sfSprite *background4;
    sfSprite *dark;
    sfSprite *toggle_grid_hint;
    sfSprite *erase_hint;
    sfSprite *hud_down;
    sfSprite *menu_editor;
    sfSprite *main_menu;
    sfSprite *defend_point;
    sfSprite *defend_point_button;
    sfSprite *enemy_point;
    sfSprite *gold;
    sfSprite *enemy_point_button;
    sfSprite *start_button;
    sfSprite *campaign_button;
    sfSprite *custom_level_button;
    sfSprite *settings_button;
    sfSprite *settings_button_p;
    sfSprite *settings_menu;
    sfSprite *pause_menu;
    sfSprite *build_menu;
    sfSprite *winlose_tab;
    sfSprite *stars;
    sfSprite *upgrade_menu;
    sfSprite *exit_button;
    sfSprite *exit_button_p;
    sfSprite *resume_button;
    sfSprite *save_button;
    sfSprite *load_button;
    sfSprite *back_start_button;
    sfSprite *map_editor_button;
    sfSprite *apply_button;
    sfSprite *back_button;
    sfSprite *vol_up_button;
    sfSprite *vol_down_button;
    sfSprite *vol_bar;
    sfSprite *prev_button;
    sfSprite *next_button;
    sfSprite *back_how_to_button;
    sfSprite *x640_button;
    sfSprite *x960_button;
    sfSprite *x1280_button;
    sfSprite *x1920_button;
    sfSprite *x2560_button;
    sfSprite *tree_button;
    sfSprite *text_zone;
    sfSprite *rock_button;
    sfSprite *buildable_button;
    sfSprite *u_button;
    sfSprite *d_button;
    sfSprite *l_button;
    sfSprite *r_button;
    sfSprite *button_lvl1;
    sfSprite *button_lvl2;
    sfSprite *button_lvl3;
    sfSprite *button_lvl4;
    sfSprite *back_mainmenu_endbutton;
    sfSprite *continue_button;
    sfSprite *retry_button;
    sfSprite *help_button;
    sfSprite *how_to_play_sprite;
    sfSprite *selected_tower;
    sfSprite *hud_tw_dmg_sprt;
    sfSprite *hud_tw_atckspd_sprt;
    sfSprite *hud_tw_range_sprt;
    sfSprite *winlose_header;
    sfRectangleShape *mogus_hitbox_hint;
    sfRectangleShape *cursor_hitbox;
    sfTexture *mage1_preview;
    sfTexture *archer1_preview;
    sfTexture *catapult1_preview;
    sfTexture *supp1_preview;
    sfTexture *straight_path;
    sfTexture *T_path;
    sfTexture *L_path;
    sfTexture *X_path;
    sfTexture *path_arrow;
    sfTexture *tree;
    sfTexture *rock;
    sfTexture *buildable;
    sfTexture *type1_texture;
    sfTexture *type1_death;
    sfTexture *type2_texture;
    sfTexture *type2_run;
    sfTexture *type2_death;
    sfTexture *type3_texture;
    sfTexture *frost_effect;
    sfTexture *weakness_effect;
    sfTexture *explosion_effect;
    sfTexture *header_win;
    sfTexture *header_lose;
    sfTexture *empty_texture;
    sfClock *clock;
    sfTime time;
    grid_rect **grid;
    sfBool fullscreen;
    sfBool load_success;
    sfMusic *menu_music;
    sfSound *lose_sound;
    sfSound *win_sound;
    sfSound *click_sound;
    sfSound *type1_death_sound;
    sfSound *type2_death_sound;
    sfSound *stab_sound;
    sfSound *build_sound;
    sfSound *sell_sound;
    sfSound *explosion_sound;
    sfText *p_hp_text;
    sfText *player_text;
    sfText *player_text2;
    sfText *gold_text;
    sfText *wave_text;
    sfText *wave_index_text;
    sfText *hud_tw_dmg_txt;
    sfText *hud_tw_range_txt;
    sfText *hud_tw_atckspd_txt;
    sfText *endwin_text1;
    sfText *endwin_text2;
    sfFont *font;
    char *player_string;
    char *player_string2;
    char *hud_tw_dmg_str;
    char *hud_tw_range_str;
    char *hud_tw_atckspd_str;
    char *build_txt_str4;
    char *upgrade_txt_str1;
    char *upgrade_txt_str2;
    char *wave_index_str;
    float erase;
    float end_lvl_delay;
    int i;
    int custom_level;
    int b_m_button;
    int gold_a;
    int exit_code;
    int volume;
    int vol_bar_offset;
    int connections;
    int choice;
    int main_menu_button;
    float g_scale;
    float main_clock;
    float move_clock;
    float delay_exit;
    float toggle_delay;
    float load_delay;
    float build_menu_delay;
    float seconds;
    float initial_delay;
    float start_delay;
    float level_selection_delay;
    float level_back_delay;
    float wave_cooldown;
    int x;
    int build_menu_open;
    int w;
    int j;
    int wave_index;
    int wave_nb;
    int how_to_play_open;
    int stats_visible;
    int chapter;
    int exit;
    int player_health;
    int enemies_left;
    float test_dmg;
    int gold_cooldown;
    int entry_points;
    wave **cur_wave;
    wave *head;
} tower_defense;

void init_animated_sprite(sfSprite *sprite, int frames);
sfSprite *new_sprite(char *texture_name, float x, float y);
sfVector2f get_sprite_center(sfSprite *sprite);
sfSound *set_up_new_sound(sfSound *new_sound, const char *buffer_location);
sfSprite *new_sprite2(sfTexture *texture, float x, float y);
tower_defense execute_game_loop(tower_defense td, int chapter);
tower_defense load_map_loop(tower_defense td);
tower_defense level_selection(tower_defense td);
