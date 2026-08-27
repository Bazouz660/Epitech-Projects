/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann (copie 2)
** File description:
** prototypes.h
*/

#include "rpg.h"
#include "structs.h"

#pragma once

// Utils
char *get_word(char **tab, int min, int max);
char **str_to_word(const char *str, const char *delim);
int nb_words(char **tab);
char* open_text(char *filepath);
int my_strlen(char *str);
sfRenderWindow *create_window(char const *title);
sfSprite *new_sprite(char *texture_name, float x, float y);
sfSound *new_sound(sfSound *new_sound, const char *buffer_location);
void init_animated_sprite(sfSprite *sprite, int columns, int rows);
sfSprite *set_sprite_pos(sfSprite *sprite, float posX, float posY);
int upt_anim_sprite(sfSprite *sprite, sfVector2i frames,
sfBool looping, int frame_index);
sfVector2f get_sprite_center(sfSprite *sprite);
float random_float(float scale);
int random_number(int min_num, int max_num);
sfVertex add_vertex_circular(core_t *c, float *radius,
float i, sfVector2f center);
int positive(int nb);
sfVector2f get_rect_center(sfRectangleShape *rect);
sfFloatRect init_frect(float left, float top, float width, float height);
int random_between(int lower, int upper);
sfVector2f init_fvect(float x, float y);
sfIntRect init_irect(int left, int top, int width, int height);
char *my_int_to_str(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strcat(char *dest, char const *src);
char **my_str_to_word_array(char *str);
int my_atoi(char *str);
sfBool mouse_intersect_rect(core_t *c, sfFloatRect rect);
sfBool get_mouse_intersect_view(core_t *c, sfFloatRect to_check);
int count_nodes(enemies_t *node);
void init_sftext(core_t *c, sfText **txt, int size);
void *set_rectshape_pos(sfRectangleShape *rect, float posX, float posY);
int my_strcmp(char const *s1, char const *s2);

// Game
void update_clock(core_t *c);

// Enemies
void delete_node(enemies_t **head, enemies_t *del_node);
void add_node(core_t *c, enemies_t **head, int type, int i);
void create_enemies(core_t *c, int nb);
void init_enemies_textures(core_t *c);
void e_handle_anims(core_t *c);
void handle_enemies_direction(core_t *c);
void e_play_atk1(core_t *c, enemies_t *node);
void e_play_walk(core_t *c, enemies_t *node);
void e_play_death(core_t *c, enemies_t *node);
void e_play_idle(core_t *c, enemies_t *node);
void create_type1(core_t *c, entity_t *entity, int i);
void create_type2(core_t *c, entity_t *entity);
void create_type3(core_t *c, entity_t *entity);
void create_type4(core_t *c, entity_t *entity);
void update_anims_enemy(core_t *c, enemies_t *head);
void delete_enemy(core_t *c, enemies_t *head, int r);
void reset_enemies(core_t *c, enemies_t *head);

// Collisions
void handle_collisions(core_t *c);
void collision_loop(core_t *c, int i);
void bottom_collision(core_t *c, int i);
void top_collision(core_t *c, int i);
void right_collision(core_t *c, int i);
void left_collision(core_t *c, int i);
void e_bottom_collision(core_t *c, enemies_t *node);
void e_top_collision(core_t *c, enemies_t *node);
void e_right_collision(core_t *c, enemies_t *node);
void e_left_collision(core_t *c, enemies_t *node);
void handle_climb_inputs(core_t *c);
void handle_ladders(core_t *c);
void handle_enemies_collisions(core_t *c, enemies_t *head);
void init_stage_0_cols(core_t *c);
void init_stage_1_cols(core_t *c);
void init_stage_2_cols(core_t *c);
void init_stage_3_cols(core_t *c);

// Player Animations
void play_idle(core_t *c);
void play_jump(core_t *c);
void play_run(core_t *c);
void play_fall(core_t *c);
void play_idle_crouch(core_t *c);
void play_roll(core_t *c);
void play_pray_start(core_t *c);
void play_pray_idle(core_t *c);
void play_pray_end(core_t *c);
void play_hanging(core_t *c);
void play_stand_attack(core_t *c);
void play_run_attack(core_t *c);
void play_stand_attack_2(core_t *c);
void play_stand_attack_3(core_t *c);
void play_fall_attack(core_t *c);
void play_fall_attack_2(core_t *c);
void play_climb(core_t *c);
void play_death(core_t *c);
void animate_passive(core_t *c);
void animate_passive_2(core_t *c);
void play_jump_attack(core_t *c);
void handle_fall_atk(core_t *c);
void handle_run_attack(core_t *c);
void handle_jump_atk(core_t *c);
void handle_combos(core_t *c);
void combo_end(core_t *c);
void reset_anim(sfSprite *sprite, core_t *c);
void animate(core_t *c);

// Player States
void uncrouch(core_t *c);
void crouch(core_t *c);
void direction_handler(core_t *c);
void check_slide_grab(core_t *c);
void inv_player_direction(core_t *c);
void handle_crouch(core_t *c);
void handle_pray(core_t *c);
void hanging_handler(core_t *c);
void handle_states(core_t *c);
void handle_respawn(core_t *c);

// Player attacks
void handle_hit_hitbox(core_t *c);
void get_attack_type(core_t *c);
void create_p_hitbox(core_t *c, sfFloatRect bounds);
void handle_player_dmg(core_t *c);
void reset_enemy_iframes(core_t *c, enemies_t *head);
void handle_dmg(core_t *c);
void cancel_hit(core_t *c);

// Scene
void draw_scene(core_t *c);
void handle_events(core_t *c);
void handle_gravity(core_t *c);
void move_all(core_t *c);
void draw_enemies(core_t *c, enemies_t *head);
void draw_hud(core_t *c);
void draw_particles_loop(core_t *c);
void draw_aura(core_t *c);
void update_saving_clock(core_t *c);

// Stamina
void update_stam_bar(core_t *c);
void regen_stam(core_t *c);
void handle_stam(core_t *c);

// Initialization
void init_item(core_t *c);
void variables_declarations(core_t *c);
void init_keyboard(core_t *c);
void init_player_states(core_t *c);
void init_player_textures(core_t *c);
void init_sounds(core_t *c);
void init_hud(core_t *c);
void init_player_states(core_t *c);
void init_player_states_2(core_t *c);
void init_e_spawns_0(core_t *c);
void init_campfires_0(core_t *c);
void init_colors(core_t *c);
void init_defaut_sprites(core_t *c);
void init_inventory(core_t *c);

// Inputs
void player_inputs(core_t *c);
void mouse_inputs(core_t *c);

// Misc
void render_pause_menu(core_t *c);
sfRectangleShape *create_ladder(core_t *c, sfVector2f pos);
void handle_p_menu(core_t *c);

// View
sfFloatRect view_bounds(sfView *view);
void move_view(core_t *c);

// Map
void set_map_pos(core_t *c, sfVector2f pos);
void map(core_t *c);
void rotate_map(core_t *c, sfVector2f vect);
void create_floor(sfVertexArray **walls, sfVector2f pos, sfVector2f size,
int top);
void draw_map(core_t *c);

// Particles
particles_t *create_fire_particles(core_t *c, sfVector2f emmiter_pos,
int amount, int speed);
void update_vertices(core_t *c, particle_t *head, int i);
sfVertexArray *create_particles(core_t *c, float radius, sfVector2f pos);
void animate_light(core_t *c, sfVertex *center);
void add_part(core_t *c, particle_t **head, int i);
void handle_particles(core_t *c);
void del_part(particle_t **head, particle_t *del_node);
void draw_particles(core_t *c, particle_t *head, particle_t *head2);

// Campfires
campfire_t create_campfire(core_t *c, float posx, float posy);

// Menu
void init_menu(core_t *c);
void manage_button(core_t *c);
void render_menu(core_t *c);
void place_cursor(core_t *c);
void fade_out(core_t *c, float curb, float time, sfSprite *sprite);
void fade_in(core_t *c, sfSprite *sprite);
void init_menusprite_2(core_t *c);

// Settings
void render_options(core_t *c);
void init_sound(core_t *c);
void init_option(core_t *c);
void manage_30fps(core_t *c);
void manage_60fps(core_t *c);
void manage_90fps(core_t *c);
void manage_120fps(core_t *c);
void manage_up(core_t *c);
void manage_down(core_t *c);
void manage_settings(core_t *c);
void set_alpha_option(core_t *c);
int get_mouse_intersect(core_t *c, sfSprite *sprite);

// Background
void reset_backgroundx(core_t *c);
void move_background(core_t *c);
void reset_backgroundy(core_t *c);

// Inventory
void render_inventory(core_t *c);
void move_rect(core_t *c);
void money(core_t *c);
void create_money_text(core_t *c);
void level_str(core_t *c);
void create_level_text(core_t *c);
void create_vigor_text(core_t *c);
void create_stam_text(core_t *c);
void create_strength_text(core_t *c);
void create_agility_text(core_t *c);
void create_points_text(core_t *c);
void vigor_inv(core_t *c);
void stam_inv(core_t *c);
void strength_inv(core_t *c);
void agility_inv(core_t *c);
void points_inv(core_t *c);
void move_plus(core_t *c);
void handle_plus(core_t *c);
void pickup_item(core_t *c, int i);
void move_rect(core_t *c);
void move_anim_inventory(core_t *c);
void move_slot(core_t *c, int i, sfVector2f pos);
void handle_map_pan(core_t *c);
void reset_selected_item(core_t *c);
void place_selected_i(core_t *c);
void handle_selected_item(core_t *c);
void show_description_inv(core_t *c);

// Save
void load_save(core_t *c);
void save_in_file(core_t *c);

// Spikes
void handle_spikes_dmg_p(core_t *c);
void e_spikes_dmg_loop(core_t *c, enemies_t *head, sfFloatRect rect1);
void handle_spikes_dmg_e(core_t *c, enemies_t *head);

//Dialogue
void create_exclamation_point(core_t *c);
void render_quest(core_t *c);
void render_dialogue(core_t *c);
void create_dialogue(core_t *c);
void blacksmith_dialogue(core_t *c);
void firstnpc_dialogue(core_t *c);
void stop_dialogue(core_t *c, char *str);
void display_dialogue(core_t *c, char *str);
void display_box(core_t *c);
void reset_dialogue(core_t *c);

// Destroy
void destroy_all(core_t *c);

// Stats
void handle_vigor(core_t *c);
void handle_stam_i(core_t *c);
void handle_strength(core_t *c);
void handle_agility(core_t *c);
void handle_exp(core_t *c);
void handle_lvl_stats(core_t *c);

//Shop
void init_shop_scene(core_t *c);
void event_shop(core_t *c);
void render_shop(core_t *c);
void init_trading(core_t *c);
void handle_trading(core_t *c);
void randomise_shop_inventory(core_t *c);
void init_trading(core_t *c);

// Chests
void draw_chests(core_t *c);
void handle_chests(core_t *c);
void animate_chests(core_t *c);

//npc
npc_t create_npc(core_t *c, float posx, float posy, char *path);
sfRectangleShape *place_npc(core_t *c, sfVector2f pos);
void blacksmith_anim(core_t *c);
void npc_quest_anim(core_t *c);
void update_anim_bs(core_t *c);
void npc_wizard_anim(core_t *c);
void npc_bluewizard_anim(core_t *c);

// Stage
void init_stage_0(core_t *c);
void init_stage_1(core_t *c);
void init_stage_2(core_t *c);
void init_stage_3(core_t *c);
void init_e_spawns_0(core_t *c);
void init_e_spawns_1(core_t *c);
void init_e_spawns_2(core_t *c);
void init_e_spawns_3(core_t *c);
void handle_lvl_change(core_t *c);