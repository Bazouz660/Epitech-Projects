/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_stage_1.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_e_spawns_1(core_t *c)
{
    c->stage[1].spawn_nb = 16;
    c->stage[1].e_spawns = malloc(sizeof(sfVector2f) * 17);
    c->stage[1].e_spawns[0] = init_fvect(936, 1886);
    c->stage[1].e_spawns[1] = init_fvect(562, 1884);
    c->stage[1].e_spawns[2] = init_fvect(2978, 1734);
    c->stage[1].e_spawns[3] = init_fvect(3170, 2788);
    c->stage[1].e_spawns[4] = init_fvect(3655, 2788);
    c->stage[1].e_spawns[5] = init_fvect(4783, 2500);
    c->stage[1].e_spawns[6] = init_fvect(5100, 2500);
    c->stage[1].e_spawns[7] = init_fvect(5700, 2500);
    c->stage[1].e_spawns[8] = init_fvect(6684, 2500);
    c->stage[1].e_spawns[9] = init_fvect(6115, 2500);
    c->stage[1].e_spawns[10] = init_fvect(3500, 640);
    c->stage[1].e_spawns[11] = init_fvect(3742, 640);
    c->stage[1].e_spawns[12] = init_fvect(4804, 640);
    c->stage[1].e_spawns[13] = init_fvect(3850, -370);
    c->stage[1].e_spawns[14] = init_fvect(3430, -370);
    c->stage[1].e_spawns[15] = init_fvect(2894, -370);
    c->stage[1].enemies_nb = 16;
    create_enemies(c, c->stage[1].enemies_nb);
}

void init_campfires_1(core_t *c)
{
    c->stage[1].campfires = malloc(sizeof(campfire_t) * 4);
    c->stage[1].campfires[0] = create_campfire(c, 1000, 2820);
    c->stage[1].campfires[1] = create_campfire(c, 5860, 960);
    c->stage[1].campfires[2] = create_campfire(c, 2184, 708);
    c->stage[1].campfires[3].lit = -1;
}

static void init_spikes_1(core_t *c, int si)
{
    c->stage[si].spikes_nb = 1;
    c->stage[si].spikes = malloc(sizeof(sfSprite *) * 4);
    c->stage[si].spikes[1] = NULL;
    for (int i = 0; i < c->stage[si].spikes_nb; i++) {
        c->stage[si].spikes[i] = sfSprite_create();
        sfSprite_setTexture(c->stage[si].spikes[i], c->textures.spikes, True);
        sfSprite_setScale(c->stage[si].spikes[i], init_fvect(1.8, 1.8));
    }
    set_sprite_pos(c->stage[si].spikes[0], 5350, 900);
}

static void set_pos_chests(core_t *c, sfVector2f pos, int si, int direction, int i)
{
    sfSprite_setOrigin(c->stage[si].chests[i].sp, get_sprite_center(c->stage[si].chests[i].sp));
    sfSprite_setOrigin(c->stage[si].chests[i].glow, get_sprite_center(c->stage[si].chests[i].glow));
    sfSprite_setOrigin(c->stage[si].chests[i].prompt, get_sprite_center(c->stage[si].chests[i].prompt));
    sfSprite_setOrigin(c->stage[si].chests[i].loot, get_sprite_center(c->stage[si].chests[i].loot));
    sfSprite_setPosition(c->stage[si].chests[i].sp, pos);
    sfSprite_setScale(c->stage[si].chests[i].sp, init_fvect((3 * direction), 3));
    set_sprite_pos(c->stage[si].chests[i].prompt, pos.x, pos.y - 50);
    set_sprite_pos(c->stage[si].chests[i].loot, pos.x - 20, pos.y + 10);
    sfSprite_setScale(c->stage[si].chests[i].prompt, init_fvect(0.7, 0.7));
}

static void init_chests_1(core_t *c, int si)
{
    sfVector2f pos;

    c->stage[si].chests = malloc(sizeof(chest_t) * 7);
    c->stage[si].chests[0].sp = new_sprite("sprites/chests/chest1.png", 3, 3);
    c->stage[si].chests[0].glow = new_sprite("sprites/glow_effect.png", 1, 1);
    c->stage[si].chests[0].loot = sfSprite_create();
    c->stage[si].chests[0].prompt = sfSprite_create();
    sfSprite_setTexture(STAGE.chests[0].prompt, c->textures.interact_prompt,
    False);
    for (int i = 1; i < 6; i++) {
        STAGE.chests[i].sp = sfSprite_copy(STAGE.chests[0].sp);
        STAGE.chests[i].glow = sfSprite_copy(STAGE.chests[0].glow);
        STAGE.chests[i].loot = sfSprite_copy(STAGE.chests[0].loot);
        STAGE.chests[i].prompt = sfSprite_copy(STAGE.chests[0].prompt);
    }
    c->stage[si].chests[6].sp = NULL;
    for (int i = 0; c->stage[si].chests[i].sp; i++) {
        init_animated_sprite(c->stage[si].chests[i].sp, 10, 1);
        STAGE.chests[i].opened = 0;
        STAGE.chests[i].level = 1;
        STAGE.chests[i].frame_index = 1;
        STAGE.chests[i].anim_clock = 0;
        STAGE.chests[i].loot_anim_clock = 0;
        STAGE.chests[i].empty = 0;
    }
    STAGE.chests[0].loot_id = random_between(3, 4);
    STAGE.chests[1].loot_id = random_between(13, 16);
    STAGE.chests[2].loot_id = random_between(1, 10);
    STAGE.chests[3].loot_id = random_between(1, 8);
    STAGE.chests[4].loot_id = random_between(13, 17);
    STAGE.chests[5].loot_id = random_between(1, 10);
    set_pos_chests(c, init_fvect(3130, 1725), si, 1, 0);
    set_pos_chests(c, init_fvect(6900, 2553), si, 1, 1);
    set_pos_chests(c, init_fvect(3360, -355), si, 1, 2);
    set_pos_chests(c, init_fvect(3530, -355), si, -1, 3);
    set_pos_chests(c, init_fvect(2740, 2347), si, -1, 4);
    set_pos_chests(c, init_fvect(1176, 1860), si, 1, 5);
}

static void init_ladders_1(core_t *c, int si)
{
    c->stage[si].la = malloc(sizeof(ladder_t) * 44);
    for (int i = 0; i < 13; i++) {
        c->stage[si].la[i].ladder = create_ladder(c, init_fvect(6150, 800 + (150 * i)));
    }
    for (int i = 13; i < 23; i++) {
        c->stage[si].la[i].ladder = create_ladder(c, init_fvect(1920, -420 + (150 * (i - 13))));
    }
    for (int i = 23; i < 30; i++) {
        c->stage[si].la[i].ladder = create_ladder(c, init_fvect(4370, -1230 + (150 * (i - 23))));
    }
    for (int i = 30; i < 33; i++) {
        c->stage[si].la[i].ladder = create_ladder(c, init_fvect(500, 2815 + (150 * (i - 30))));
    }
    c->stage[si].la[33].ladder = NULL;
}

void init_stage_1(core_t *c)
{
    int si = 1;
    
    init_stage_1_cols(c);
    c->stage[si].bg = new_sprite("sprites/level/lvl1.png", 1, 1);
    set_sprite_pos(c->stage[si].bg, -1000, -2700);
    c->stage_index = si;
    c->stage[si].exit_rect = init_frect(4311, -1190, 218, 200);
    c->stage[si].entry_rect = init_frect(459, 2938, 214, 172);
    c->stage[si].floors = 3;
    c->stage[si].floor_index = 0;
    c->stage[si].map_boundaries.left = 0;
    c->stage[si].map_boundaries.width = 7000;
    c->stage[si].map_boundaries.top = -2000;
    c->stage[si].floor_rect = malloc(sizeof(sfFloatRect) * 3);
    c->stage[si].floor_rect[0] = init_frect(46, 825, 7050, 2175);
    c->stage[si].floor_rect[1] = init_frect(1661, -281, 5435, 1106);
    c->stage[si].floor_rect[2] = init_frect(1661, -1050, 3300, 769);
    init_ladders_1(c, si);
    c->stage[si].npc = malloc(sizeof(npc_t) * 3);
    c->stage[si].npc[0] = create_npc(c, 500, 2700, "sprites/npc/blacksmith.png");
    c->stage[si].npc[1] = create_npc(c, 700, 2640, "sprites/npc/npc_start.png");
    c->stage[si].npc[2].npc_sp = NULL;
    init_spikes_1(c, si);
    npc_quest_anim(c);
    blacksmith_anim(c);
    init_campfires_1(c);
    set_sprite_pos(c->shop.shop_s, 3000, 920);
    init_e_spawns_1(c);
    init_chests_1(c, si);
}
