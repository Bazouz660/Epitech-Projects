/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_stage_2.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_e_spawns_2(core_t *c)
{
    c->stage[2].spawn_nb = 12;
    c->stage[2].enemies_nb = 12;
    c->stage[2].e_spawns = malloc(sizeof(sfVector2f) * 13);
    c->stage[2].e_spawns[0] = init_fvect(230, 1655);
    c->stage[2].e_spawns[1] = init_fvect(20, 1644);
    c->stage[2].e_spawns[2] = init_fvect(1314, 1608);
    c->stage[2].e_spawns[3] = init_fvect(4885, 1327);
    c->stage[2].e_spawns[4] = init_fvect(4613, 1327);
    c->stage[2].e_spawns[5] = init_fvect(3867, 284);
    c->stage[2].e_spawns[6] = init_fvect(3286, 284);
    c->stage[2].e_spawns[7] = init_fvect(2667, 284);
    c->stage[2].e_spawns[8] = init_fvect(2056, 284);
    c->stage[2].e_spawns[9] = init_fvect(1438, 284);
    c->stage[2].e_spawns[10] = init_fvect(2276, -825);
    c->stage[2].e_spawns[11] = init_fvect(-1476, 2716);
    create_enemies(c, c->stage[2].enemies_nb);
}

void init_campfires_2(core_t *c)
{
    c->stage[2].campfires = malloc(sizeof(campfire_t) * 3);
    c->stage[2].campfires[0] = create_campfire(c, 50, 2825);
    c->stage[2].campfires[1] = create_campfire(c, 3500, 1420);
    c->stage[2].campfires[2].lit = -1;
}

static void init_spikes_2(core_t *c, int si)
{
    c->stage[si].spikes_nb = 12;
    c->stage[si].spikes = malloc(sizeof(sfSprite *) * 20);
    for (int i = 0; i < c->stage[si].spikes_nb; i++) {
        c->stage[si].spikes[i] = sfSprite_create();
        sfSprite_setTexture(c->stage[si].spikes[i], c->textures.spikes, True);
        sfSprite_setScale(c->stage[si].spikes[i], init_fvect(1.8, 1.8));
    }
    c->stage[si].spikes[c->stage[si].spikes_nb] = NULL;
    set_sprite_pos(c->stage[si].spikes[0], -625, 1830);
    set_sprite_pos(c->stage[si].spikes[1], -425, 1830);
    set_sprite_pos(c->stage[si].spikes[2], 315, 1830);
    set_sprite_pos(c->stage[si].spikes[3], 515, 1830);

    for (int i = 4; i < c->stage[si].spikes_nb; i++)
        set_sprite_pos(c->stage[si].spikes[i], 1510 + (200 * (i - 4)), 2780);
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

static void init_chests_2(core_t *c, int si)
{
    c->stage[si].chests = malloc(sizeof(chest_t) * 2);
    c->stage[si].chests[0].sp = new_sprite("sprites/chests/chest1.png", 3, 3);
    c->stage[si].chests[0].glow = new_sprite("sprites/glow_effect.png", 1, 1);
    c->stage[si].chests[0].loot = sfSprite_create();
    c->stage[si].chests[0].prompt = sfSprite_create();
    sfSprite_setTexture(c->stage[si].chests[0].prompt, c->textures.interact_prompt,
    False);
    c->stage[si].chests[1].sp = NULL;
    for (int i = 0; c->stage[si].chests[i].sp; i++) {
        init_animated_sprite(c->stage[si].chests[i].sp, 10, 1);
        c->stage[si].chests[i].opened = 0;
        c->stage[si].chests[i].level = 1;
        c->stage[si].chests[i].frame_index = 1;
        c->stage[si].chests[i].anim_clock = 0;
        c->stage[si].chests[i].loot_anim_clock = 0;
        c->stage[si].chests[i].empty = 0;
    }
    STAGE.chests[0].loot_id = random_between(1, 9);
    set_pos_chests(c, init_fvect(740, 338), si, -1, 0);
}

static void init_ladders_2(core_t *c, int si)
{
    c->stage[si].la = malloc(sizeof(ladder_t) * 22);
    c->stage[si].la[0].ladder = create_ladder(c, init_fvect(4700, 1330));
    c->stage[si].la[1].ladder = create_ladder(c, init_fvect(4700, 1180));
    c->stage[si].la[2].ladder = create_ladder(c, init_fvect(4700, 1030));
    c->stage[si].la[3].ladder = create_ladder(c, init_fvect(4700, 880));
    c->stage[si].la[4].ladder = create_ladder(c, init_fvect(4700, 730));
    c->stage[si].la[5].ladder = create_ladder(c, init_fvect(4700, 580));
    c->stage[si].la[6].ladder = create_ladder(c, init_fvect(4700, 430));
    c->stage[si].la[7].ladder = create_ladder(c, init_fvect(4700, 280));
    c->stage[si].la[8].ladder = create_ladder(c, init_fvect(1250, 320));
    c->stage[si].la[9].ladder = create_ladder(c, init_fvect(1250, 170));
    c->stage[si].la[10].ladder = create_ladder(c, init_fvect(1250, 20));
    c->stage[si].la[11].ladder = create_ladder(c, init_fvect(1250, -130));
    c->stage[si].la[12].ladder = create_ladder(c, init_fvect(1250, -280));
    c->stage[si].la[13].ladder = create_ladder(c, init_fvect(1250, -430));
    c->stage[si].la[14].ladder = create_ladder(c, init_fvect(1250, -580));
    c->stage[si].la[15].ladder = create_ladder(c, init_fvect(1250, -730));
    for (int i = 16; i < 19; i++)
        c->stage[si].la[i].ladder = create_ladder(c, init_fvect(575, 2799 + ((i - 16) * 150)));
    c->stage[si].la[19].ladder = NULL;
}

void init_stage_2(core_t *c)
{
    int si = 2;

    init_stage_2_cols(c);
    c->stage[si].bg = new_sprite("sprites/level/lvl2.png", 1, 1);
    set_sprite_pos(c->stage[si].bg, -2900, -2020);
    sfSprite_setScale(c->door_bg,
    init_fvect(3.01,
    sfSprite_getScale(c->door_bg).y));
    set_sprite_pos(c->door_bg, 4186.5, -1060.5);
    c->stage_index = si;
    c->stage[si].exit_rect = init_frect(4370, -895, 300, 231);
    c->stage[si].entry_rect = init_frect(540, 3000, 218, 198);
    c->stage[si].floors = 3;
    c->stage[si].floor_index = 0;
    c->stage[si].map_boundaries.left = 0;
    c->stage[si].map_boundaries.width = 7000;
    c->stage[si].map_boundaries.top = -4000;
    c->stage[si].floor_rect = malloc(sizeof(sfFloatRect) * 4);
    c->stage[si].floor_rect[0] = init_frect(-1800, 416, 7000, 2700);
    c->stage[si].floor_rect[1] = init_frect(388, -672, 4812, 1088);
    c->stage[si].floor_rect[2] = init_frect(388, -1421, 4044, 749);
    init_ladders_2(c, si);
    c->stage[si].npc = malloc(sizeof(npc_t) * 3);
    c->stage[si].npc[0] = create_npc(c, 500, 2700, "sprites/npc/blacksmith.png");
    c->stage[si].npc[1] = create_npc(c, 700, 2640, "sprites/npc/npc_start.png");
    c->stage[si].npc[2].npc_sp = NULL;
    init_spikes_2(c, si);
    npc_quest_anim(c);
    blacksmith_anim(c);
    init_campfires_2(c);
    set_sprite_pos(c->shop.shop_s, 3000, 920);
    init_e_spawns_2(c);
    init_chests_2(c, si);
}
