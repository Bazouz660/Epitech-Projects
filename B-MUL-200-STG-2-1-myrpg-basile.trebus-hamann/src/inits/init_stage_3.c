/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_stage_2.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_e_spawns_3(core_t *c)
{
    c->stage[3].spawn_nb = 10;
    c->stage[3].e_spawns = malloc(sizeof(sfVector2f) * 10);
    c->stage[3].e_spawns[0] = init_fvect(283, 3802);
    c->stage[3].e_spawns[1] = init_fvect(2335, 3291);
    c->stage[3].e_spawns[2] = init_fvect(2600, 3291);
    c->stage[3].e_spawns[3] = init_fvect(2894, 3291);
    c->stage[3].e_spawns[4] = init_fvect(2988, 2486);
    c->stage[3].e_spawns[5] = init_fvect(3452, 2486);
    c->stage[3].e_spawns[6] = init_fvect(4343, 1564);
    c->stage[3].e_spawns[7] = init_fvect(6277, 1561);
    c->stage[3].e_spawns[8] = init_fvect(6910, 1561);
    c->stage[3].e_spawns[9] = init_fvect(7440, 1561);
    c->stage[3].enemies_nb = 10;
    create_enemies(c, c->stage[3].enemies_nb);
}

void init_campfires_3(core_t *c)
{
    c->stage[3].campfires = malloc(sizeof(campfire_t) * 3);
    c->stage[3].campfires[0] = create_campfire(c, 50, 2825);
    c->stage[3].campfires[1] = create_campfire(c, 1988, 2577);
    c->stage[3].campfires[2].lit = -1;
}

static void init_spikes_3(core_t *c, int si)
{
    STAGE.spikes_nb = 7;
    STAGE.spikes = malloc(sizeof(sfSprite *) * 20);
    for (int i = 0; i < STAGE.spikes_nb; i++) {
       STAGE.spikes[i] = sfSprite_create();
       sfSprite_setTexture(STAGE.spikes[i], c->textures.spikes, True);
       sfSprite_setScale(STAGE.spikes[i], init_fvect(1.8, 1.8));
    }
    STAGE.spikes[STAGE.spikes_nb] = NULL;
    for (int i = 0; i < 3; i++)
       set_sprite_pos(STAGE.spikes[i], 900 + (200 * (i)), 3800);
    set_sprite_pos(STAGE.spikes[3], -1083, 3820);
    for (int i = 4; i < 7; i++)
       set_sprite_pos(STAGE.spikes[i], 7731 + (200 * (i - 4)), 3485);
}

static void set_pos_chests(core_t *c, sfVector2f pos, int si, int direction, int i)
{
    sfSprite_setOrigin(STAGE.chests[i].sp, get_sprite_center(STAGE.chests[i].sp));
    sfSprite_setOrigin(STAGE.chests[i].glow, get_sprite_center(STAGE.chests[i].glow));
    sfSprite_setOrigin(STAGE.chests[i].prompt, get_sprite_center(STAGE.chests[i].prompt));
    sfSprite_setOrigin(STAGE.chests[i].loot, get_sprite_center(STAGE.chests[i].loot));
    sfSprite_setPosition(STAGE.chests[i].sp, pos);
    sfSprite_setScale(STAGE.chests[i].sp, init_fvect((3 * direction), 3));
    set_sprite_pos(STAGE.chests[i].prompt, pos.x, pos.y - 50);
    set_sprite_pos(STAGE.chests[i].loot, pos.x - 20, pos.y + 10);
    sfSprite_setScale(STAGE.chests[i].prompt, init_fvect(0.7, 0.7));
}

static void init_chests_3(core_t *c, int si)
{
    STAGE.chests = malloc(sizeof(chest_t) * 4);
    STAGE.chests[0].sp = new_sprite("sprites/chests/chest1.png", 3, 3);
    STAGE.chests[0].glow = new_sprite("sprites/glow_effect.png", 1, 1);
    STAGE.chests[0].loot = sfSprite_create();
    STAGE.chests[0].prompt = sfSprite_create();
    sfSprite_setTexture(STAGE.chests[0].prompt,
    c->textures.interact_prompt, False);
    for (int i = 1; i < 4; i++) {
        STAGE.chests[i].sp = sfSprite_copy(STAGE.chests[0].sp);
        STAGE.chests[i].glow = sfSprite_copy(STAGE.chests[0].glow);
        STAGE.chests[i].loot = sfSprite_copy(STAGE.chests[0].loot);
        STAGE.chests[i].prompt = sfSprite_copy(STAGE.chests[0].prompt);
    }
    STAGE.chests[4].sp = NULL;
    for (int i = 0; STAGE.chests[i].sp; i++) {
        init_animated_sprite(STAGE.chests[i].sp, 10, 1);
        STAGE.chests[i].opened = 0;
        STAGE.chests[i].level = 1;
        STAGE.chests[i].frame_index = 1;
        STAGE.chests[i].anim_clock = 0;
        STAGE.chests[i].loot_anim_clock = 0;
        STAGE.chests[i].empty = 0;
    }
    STAGE.chests[0].loot_id = random_between(3, 10);
    STAGE.chests[1].loot_id = random_between(13, 18);
    STAGE.chests[2].loot_id = random_between(5, 11);
    set_pos_chests(c, init_fvect(-1262, 3855), si, -1, 0);
    set_pos_chests(c, init_fvect(2075, 3364), si, -1, 1);
    set_pos_chests(c, init_fvect(4070, 1606), si, -1, 2);
}

static void init_ladders_3(core_t *c)
{
    STAGE.la = malloc(sizeof(ladder_t) * 20);
    for (int i = 0; i < 9; i++)
        STAGE.la[i].ladder = create_ladder(c, init_fvect(-1062, 2669 + (i * 150)));
    for (int i = 9; i < 16; i++)
        STAGE.la[i].ladder = create_ladder(c, init_fvect(4729, 1600 + ((i - 9) * 150)));
    STAGE.la[16].ladder = NULL;
}

void init_stage_3(core_t *c)
{
    init_stage_3_cols(c);
    c->stage_index = 3;
    STAGE.bg = new_sprite("sprites/level/lvl3.png", 1, 1);
    set_sprite_pos(STAGE.bg, -2000, 310);
    sfSprite_setScale(c->door_bg,
    init_fvect(-3.01,
    sfSprite_getScale(c->door_bg).y));
    set_sprite_pos(c->door_bg, -1211, 2298);
    STAGE.exit_rect = init_frect(6169, -127, 205, 118);
    STAGE.entry_rect = init_frect(-1513, 2507, 130, 300);
    STAGE.floors = 1;
    STAGE.floor_index = 0;
    STAGE.map_boundaries.left = 0;
    STAGE.map_boundaries.width = 7000;
    STAGE.map_boundaries.top = -2000;
    STAGE.floor_rect = malloc(sizeof(sfFloatRect) * 2);
    STAGE.floor_rect[0] = init_frect(-1800, 876, 10300, 3300);
    init_ladders_3(c);
    STAGE.npc = malloc(sizeof(npc_t) * 3);
    STAGE.npc[0] = create_npc(c, 500, 2700, "sprites/npc/blacksmith.png");
    STAGE.npc[1] = create_npc(c, 700, 2640, "sprites/npc/npc_start.png");
    STAGE.npc[2].npc_sp = NULL;
    init_spikes_3(c, c->stage_index);
    npc_quest_anim(c);
    blacksmith_anim(c);
    init_campfires_3(c);
    set_sprite_pos(c->shop.shop_s, 3000, 920);
    init_e_spawns_3(c);
    init_chests_3(c, c->stage_index);
}
