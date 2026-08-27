/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann (copie 2)
** File description:
** structs.h
*/

#include "rpg.h"
#include "defines.h"

typedef struct read_file_s {
    FILE *file;
    char *line;
    size_t len;
    int i;
    int lines;
} read_file_t;

typedef struct p_health_bar_s {
    sfSprite *sp_bar_hpp;
    sfSprite *sp_rbar_hpp;
    sfVector2f hppbar_size;
    sfVector2f hppbar_pos;
    sfIntRect rect;
} p_health_bar_t;

typedef struct p_stam_bar_s {
    sfSprite *sp_bar_sp;
    sfSprite *sp_gbar_sp;
    sfVector2f spbar_size;
    sfVector2f spgbar_size;
    sfVector2f spbar_pos;
    sfIntRect rect;
} p_stam_bar_t;

typedef struct hotbar_s {
    sfSprite *bg;
    sfSprite *i_a;
    sfSprite *i_b;
    sfSprite *i_c;
    sfSprite *i_d;
} hotbar_t;

typedef struct inv_prompt_s {
    sfSprite *bg;
    sfText *key;
} inv_prompt_t;

typedef struct hud_s {
    p_stam_bar_t p_stam;
    p_health_bar_t p_health;
    hotbar_t hotbar;
    inv_prompt_t inv_prom;
} hud_t;

typedef struct en_tex_dic_s {
    sfTexture ***textures;
} en_tex_dic_t;

typedef struct i_stats_s {
    float dmg_boost;
    int xp_reward;
    float life_reg;
    float armor;
    int cost;
} i_stats_t;

typedef struct slot_s {
    sfRectangleShape *rect;
    sfSprite *obj;
    i_stats_t stats;
    int id;
} slot_t;

typedef struct shop_s{
    sfSprite *back_s;
    sfTexture *back_t;
    bool shop_scene;
    sfSprite *shop_s;
    sfRectangleShape *blacksmith_rect;
    sfRectangleShape *door;
    sfRectangleShape *shop_entrance;
    sfSprite *door_leaves;
    sfSprite *shop_inv;
    sfSprite *trade_prompt;
    sfTexture *door_leavet;
    slot_t *slots;
    int trading;
    int mem_slot;
} shop_t;

typedef struct desc_s {
    sfSprite *bg;
    sfText *txt_armor;
    sfText *txt_dmg;
    sfText *txt_life_reg;
    sfText *txt_xp_gain;
    sfText *txt_cost;
} desc_t;

typedef struct inventory_s {
    slot_t *slots;
    sfText *moneytxt;
    sfText *leveltxt;
    sfText *vigortxt;
    sfText *stamtxt;
    sfText *pointstxt;
    sfText *strengthtxt;
    sfText *agilitytxt;
    sfText *ptstospendtxt;
    sfRectangleShape *black_rect;
    sfSprite *plus_1;
    sfSprite *plus_2;
    sfSprite *plus_3;
    sfSprite *plus_4;
    sfSprite *book_s;
    sfSprite *selected_i;
    sfTexture *book_t;
    sfTexture *button_t;
    sfIntRect button_rect;
    desc_t desc;
    int status;
    int selected_id;
    int mem_slot;
}inventory_t;

typedef struct health_bar_s {
    sfRectangleShape *red_bar;
    sfRectangleShape *coutour;
} health_bar_t;

typedef struct entity_s {
    health_bar_t hb;
    sfVector2f scale;
    sfVector2f pos;
    sfVector2f vect;
    sfSprite *sprite;
    sfVector2i pt_frames;
    sfTexture **textures;
    sfRectangleShape *hitbox;
    sfRectangleShape *hit_hitbox;
    float speed;
    int reward_xp;
    int reward_gold;
    float dmg;
    float anim_clock;
    float anim_speed;
    float health;
    float health_mem;
    float hurt_clock;
    float atk_cooldown;
    float atk_cooldown_clock;
    int type;
    int anim_state;
    int frame_index;
    int direction;
    bool anim_loop;
    bool can_be_hit;
    bool attacking;
} entity_t;

typedef struct enemies_s {
    entity_t entity;
    struct enemies_s *next;
    struct enemies_s *prev;
} enemies_t;

typedef struct ladder_s {
    sfRectangleShape *ladder;
} ladder_t;

typedef struct item_s {
    int id;
    int type;
    i_stats_t stats;
    sfSprite *object_s;
    sfTexture *object_t;
} item_t;

typedef struct particle_s {
    sfVertex vertex;
    float life_time;
    int speed;
    int index;
    float decay;
    struct particle_s *next;
    struct particle_s *prev;
} particle_t;

typedef struct particles_s {
    particle_t *part_head;
    sfVector2f emmiter;
    int max;
    int amount;
    float clock;
    float update;
} particles_t;

typedef struct campfire_s {
    sfSprite *sprite;
    particles_t *particles;
    sfVertexArray *aura;
    sfVertex *center_point;
    sfSprite *key_prompt;
    bool lit;
} campfire_t;

typedef struct option_s {
    sfRectangleShape *bar;
    sfVector2f bar_scale;
    sfSprite *sound_bar_s;
    sfSprite *up_s;
    sfSprite *down_s;
    sfSprite *leave_s;
    sfSprite **fps_sprite;
    sfTexture *sound_bar_t;
    sfTexture *down_t;
    sfTexture *leave_t;
    sfTexture *up_t;
    sfTexture **fps_texture;
    sfIntRect leave_rect;
    sfIntRect up_rect;
    sfIntRect down_rect;
    sfIntRect *button_rect;
}option_t;


typedef struct menu_s {
    sfSprite **button_s;
    sfTexture **button_t;
    sfIntRect *button_rect;
    sfFont *title_font;
    sfText *rpg_title;
    sfSprite *bg_1;
    sfSprite *bg_2;
    sfSprite *bg_3;
    sfSprite *bg_4;
    sfSprite *how_to_play_sp;
    sfSprite *how_to_play_b;
    sfSprite *embers;
    sfTexture *background_t;
    sfSprite *cursor_s;
    sfTexture *cursor_t;
    int how_to_play_open;
    float fade_out_time;
    float fade_out_curb;
    float fade_in_time;
    float fade_in_curb;
}menu_t;

typedef struct update_sprite_s {
    sfSprite *sprite;
    sfVector2i frames;
    sfBool looping;
    sfIntRect sheet_pos;
    sfVector2u txtr_size;
    int y;
} update_sprite_t;

typedef struct keyboard_s {
    sfKeyCode up;
    sfKeyCode left;
    sfKeyCode right;
    sfKeyCode down;
    sfKeyCode jump;
    sfKeyCode crouch;
    sfKeyCode sprint;
    sfKeyCode pray;
    sfKeyCode pause;
    sfKeyCode unpause;
    sfKeyCode inventory;
    sfKeyCode back;
    sfKeyCode skip;
    sfKeyCode interaction;
    sfKeyCode trade;
    bool can_click;
}keyboard_t;

typedef struct dialogue_s {
    sfSprite *enter_prompts;
    sfTexture *enter_promptt;
    sfText *dialogue_text;
    sfSprite *text_boxs;
    sfTexture *text_boxt;
    sfSprite *exclamations;
    sfTexture *exclamationt;
    char **dictionnary;
    int index;
    int init;
    int nb_words;
    int quest_kills;
    char *dialogue_str;
    char *dialogue_cpy;
    char *blacksmith_str;
    char *npc_str;
    sfBool speak_blacksmith;
    sfBool speak_npc;
    sfBool quest;
    sfBool start_quest;
    sfBool start_blacksmith;
    sfBool end_blacksmith;
} dialogue_t;

typedef struct player_states_s {
    bool grounded;
    bool falling;
    bool jumping;
    bool crouching;
    bool moving;
    bool praying;
    bool rolling;
    bool hanging;
    bool sliding;
    bool memcrouching;
    bool sprinting;
    bool side_jumping;
    bool pray_end;
    bool can_grab;
    bool roll_enabled;
    bool p_direction;
    bool anim_loop;
    bool attacking;
    bool atck_mem;
    bool combo_next;
    bool run_attack;
    bool climbing;
    bool can_be_hit;
    int jump_attack;
    int combo;
    int pray_state;
    int fall_attack;
    int player_anim_state;
    int frame_index;
} player_states_t;

typedef struct clocks_s {
    sfClock *clock;
    sfTime time;
    float dialogue_clock;
    float stam_clock;
    float stam_cooldown;
    float mvt_clock;
    float gravity_clock;
    float jump_clock;
    float player_anim_clock;
    float pray_clock;
    float roll_clock;
    float roll_cooldown;
    float side_jump_clock;
    float p_hurt_cooldown;
    float seconds;
    float inventory_clock;
    float saving_clock;
    float respawn_clock;
    float shop_clock;
} clocks_t;

typedef struct player_s {
    sfVector2f player_scale;
    sfVector2f player_pos;
    sfSprite *player_hitbox;
    sfSprite *player;
    sfVector2i pt_frames;
    sfTexture **player_textures;
    sfRectangleShape *hit_hitbox;
    sfSound **hurt_sound;
    int points;
    int vigor;
    int stam_inv;
    int strength;
    int agility;
    int exp;
    int exp_buff;
    int gold;
    int level;
    float player_speed;
    float dmg;
    float stam;
    float stam_max;
    float health;
    float health_mem;
} player_t;

typedef struct collision_s {
    sfRectangleShape **wall;
    sfFloatRect correction;
    sfFloatRect pbound;
    sfFloatRect wbound;
    sfFloatRect nextPos;
    sfVector2f global_pos;
    sfVector2f prev;
    sfVector2f next;
} collision_t;

typedef struct sounds_s {
    int volume;
    sfMusic *ambient_music;
    sfMusic *menu_music;
    sfSound *landing_sound;
    sfSound *fall_atck_impact;
    sfSound *roll_sound;
    sfSound **slash_sounds;
    sfSound *button_click;
    sfSound *p_death;
    sfSound *camp;
    sfSound *chest_open;
    sfSound *pickup;
    sfSound *t1_hurt;
    sfSound **t1_death;
    sfSound **anvil;
} sounds_t;

typedef struct movements_s {
    sfVector2f global_vect;
    double acceleration;
} movements_t;

typedef struct colors_s {
    sfColor light_color;
    sfColor fade_out;
    sfColor fade_in;
    sfColor transparent_red;
} colors_t;

typedef struct chest_s {
    sfSprite *sp;
    sfSprite *prompt;
    sfSprite *loot;
    sfSprite *glow;
    int direction;
    float anim_clock;
    float loot_anim_clock;
    int frame_index;
    int loot_id;
    int level;
    bool opened;
    bool empty;
} chest_t;

typedef struct npc_s {
    sfSprite *npc_sp;
    sfSprite *npc_start;
    bool npc_bool;
    int frame_index_bs;
    float anim_bs;
    sfVector2i frames_bs;
    sfTexture *npc_tex;
} npc_t;

typedef struct stage_s {
    sfSprite *bg;
    sfFloatRect map_boundaries;
    sfFloatRect exit_rect;
    sfFloatRect entry_rect;
    unsigned int floors;
    unsigned int floor_index;
    sfFloatRect *floor_rect;
    sfSprite **spikes;
    ladder_t *la;
    npc_t *npc;
    sfVector2f *e_spawns;
    sfVector2f *s_spawns;
    enemies_t *e;
    int spikes_nb;
    int enemies_nb;
    int spawn_nb;
    campfire_t *campfires;
    chest_t *chests;
} stage_t;

typedef struct textures_s {
    sfTexture *ladder;
    sfTexture *wall;
    sfTexture *floor;
    sfTexture *spikes;
    sfTexture *interact_prompt;
    sfTexture *empty;
} textures_t;

typedef struct m_floor_s {
    sfVertexArray **walls;
} m_floor_t;

typedef struct map_s {
    m_floor_t *m_floor;
    sfVector2f map_pos;
    sfRenderStates w_state;
    sfRenderStates f_state;
    sfVector2f pos;
    sfVector2f size;
    sfSprite *p_logo;
} map_t;

typedef struct save_s {
    sfVector2f p_pos;
    sfVector2f last_camp;
    int vigor;
    int stam;
    int agility;
    int strength;
    int lvl;
    int exp;
    int gold;
    unsigned int stage_index;
} save_t;

typedef struct p_menu_s {
    sfSprite *bg;
    sfSprite *resume;
    sfSprite *exit;
    sfSprite *main_menu;
} p_menu_t;

typedef struct core_s {
    int bt_pressed;
    int fps;
    int scene_status;
    int change_scene;
    sfRenderWindow *window;
    sfView *view;
    sfEvent event;
    sfVector2i window_pos;
    keyboard_t keys;
    player_t p;
    collision_t co;
    clocks_t clock;
    sounds_t audio;
    player_states_t pst;
    movements_t mv;
    menu_t menu;
    option_t option;
    colors_t color;
    item_t *item;
    en_tex_dic_t en_dic;
    hud_t hud;
    textures_t textures;
    inventory_t inventory;
    map_t map;
    save_t save;
    dialogue_t dialogue;
    p_menu_t p_menu;
    shop_t shop;
    stage_t *stage;
    sfSprite *black_layer;
    sfSprite *door_bg;
    sfSprite *end;
    sfSprite *you_died;
    sfSprite *background;
    sfSprite *p_saved;
    unsigned int stage_index;
    int paused;
    int saving;
    float light_clock;
} core_t;
