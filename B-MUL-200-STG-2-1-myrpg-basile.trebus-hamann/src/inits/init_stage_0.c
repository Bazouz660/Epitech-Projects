/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_stage_0.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_e_spawns_0(core_t *c)
{
    STAGE.spawn_nb = 3;
    STAGE.e_spawns = malloc(sizeof(sfVector2f) * 10);
    STAGE.e_spawns[0] = init_fvect(3600, 535);
    STAGE.e_spawns[1] = init_fvect(3000, 535);
    STAGE.e_spawns[2] = init_fvect(3200, 535);
    STAGE.enemies_nb = 3;
    create_enemies(c, c->stage[0].enemies_nb);
}

void init_campfires_0(core_t *c)
{
    STAGE.campfires = malloc(sizeof(campfire_t) * 3);
    STAGE.campfires[0] = create_campfire(c, 1000, 2780);
    STAGE.campfires[1] = create_campfire(c, 2880, 1675);
    STAGE.campfires[2].lit = -1;
}

static void set_pos_chests(core_t *c,
sfVector2f pos, int si, int direction, int i)
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

static void init_chests_0(core_t *c, int si)
{
    STAGE.chests = malloc(sizeof(chest_t) * 2);
    STAGE.chests[0].sp = new_sprite("sprites/chests/chest1.png", 3, 3);
    STAGE.chests[0].glow = new_sprite("sprites/glow_effect.png", 1, 1);
    STAGE.chests[0].loot = sfSprite_create();
    STAGE.chests[0].prompt = sfSprite_create();
    sfSprite_setTexture(STAGE.chests[0].prompt, c->textures.interact_prompt,
    False);
    for (int i = 1; i < 2; i++) {
        STAGE.chests[i].sp = sfSprite_copy(STAGE.chests[0].sp);
        STAGE.chests[i].glow = sfSprite_copy(STAGE.chests[0].glow);
        STAGE.chests[i].loot = sfSprite_copy(STAGE.chests[0].loot);
        STAGE.chests[i].prompt = sfSprite_copy(STAGE.chests[0].prompt);
    }
    STAGE.chests[2].sp = NULL;
    for (int i = 0; STAGE.chests[i].sp; i++) {
        init_animated_sprite(STAGE.chests[i].sp, 10, 1);
        STAGE.chests[i].opened = 0;
        STAGE.chests[i].level = 1;
        STAGE.chests[i].frame_index = 1;
        STAGE.chests[i].anim_clock = 0;
        STAGE.chests[i].loot_anim_clock = 0;
        STAGE.chests[i].empty = 0;
    }
    STAGE.chests[0].loot_id = random_between(3, 4);
    STAGE.chests[1].loot_id = random_between(13, 14);
    set_pos_chests(c, init_fvect(1500, 2750), si, 1, 0);
    set_pos_chests(c, init_fvect(6500, 580), si, 1, 1);
}

static void init_spikes_0(core_t *c, int si)
{
    STAGE.spikes_nb = 0;
    STAGE.spikes = malloc(sizeof(sfSprite *) * 4);
    STAGE.spikes[0] = NULL;
    for (int i = 0; i < STAGE.spikes_nb; i++) {
        sfSprite_setTexture(STAGE.spikes[i], c->textures.spikes, True);
        set_sprite_pos(STAGE.spikes[i], 2000 + (i * 200), 2700);
        sfSprite_setScale(STAGE.spikes[i], init_fvect(1.8, 1.8));
    }
}

static void init_ladders_0(core_t *c, int si)
{
    STAGE.la = malloc(sizeof(ladder_t) * 6);
    STAGE.la[0].ladder = create_ladder(c, init_fvect(6200, 0));
    STAGE.la[1].ladder = create_ladder(c, init_fvect(6200, 150));
    STAGE.la[2].ladder = create_ladder(c, init_fvect(6200, 300));
    STAGE.la[3].ladder = create_ladder(c, init_fvect(6200, 450));
    STAGE.la[4].ladder = create_ladder(c, init_fvect(6200, 600));
    STAGE.la[5].ladder = create_ladder(c, init_fvect(6200, -150));
    STAGE.la[6].ladder = NULL;
}

void init_stage_0(core_t *c)
{
    c->stage_index = 0;
    init_stage_0_cols(c);
    STAGE.bg = new_sprite("sprites/level/lvl0.png", 1, 1);
    set_sprite_pos(STAGE.bg, -950, -780);
    STAGE.exit_rect = init_frect(6169, -127, 205, 118);
    STAGE.entry_rect = init_frect(0, 0, 0, 0);
    STAGE.floors = 3;
    STAGE.floor_index = 0;
    STAGE.map_boundaries.left = 0;
    STAGE.map_boundaries.width = 6700;
    STAGE.map_boundaries.top = -127;
    STAGE.floor_rect = malloc(sizeof(sfFloatRect) * 4);
    STAGE.floor_rect[0] = init_frect(0, 1690, 5000, 1410);
    STAGE.floor_rect[1] = init_frect(1935, 628, 3065, 1064);
    STAGE.floor_rect[2] = init_frect(1935, -120, 4765, 1000);
    init_ladders_0(c, c->stage_index);
    STAGE.npc = malloc(sizeof(npc_t) * 3);
    STAGE.npc[0] = create_npc(c, 500, 2700, "sprites/npc/blacksmith.png");
    STAGE.npc[1] = create_npc(c, 141, 2595, "sprites/npc/npc_start.png");
    STAGE.npc[2].npc_sp = NULL;
    init_spikes_0(c, c->stage_index);
    npc_quest_anim(c);
    blacksmith_anim(c);
    init_campfires_0(c);
    set_sprite_pos(c->shop.shop_s, 3000, 920);
    init_e_spawns_0(c);
    init_chests_0(c, c->stage_index);
}
