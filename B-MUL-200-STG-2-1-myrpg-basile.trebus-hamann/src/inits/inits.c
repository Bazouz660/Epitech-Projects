/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** inits.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_hud(core_t *c)
{
    c->hud.hotbar.i_a = sfSprite_create();
    c->hud.hotbar.i_b = sfSprite_create();
    c->hud.hotbar.i_c = sfSprite_create();
    c->hud.p_health.sp_bar_hpp = new_sprite(HB_EMPTY, 1, 1);
    c->hud.p_health.sp_rbar_hpp = new_sprite(HB_REDBAR, 1, 1);
    c->hud.p_health.hppbar_size = init_fvect(8, 2.51);
    sfSprite_setScale(c->hud.p_health.sp_bar_hpp, c->hud.p_health.hppbar_size);
    sfSprite_setScale(c->hud.p_health.sp_rbar_hpp, c->hud.p_health.hppbar_size);
    c->hud.p_stam.sp_bar_sp = new_sprite("sprites/hud/emptybar_sp.png", 1, 1);
    c->hud.p_stam.sp_gbar_sp = new_sprite("sprites/hud/greenbar_sp.png", 1, 1);
    c->hud.p_stam.spbar_size = init_fvect(6, 2.51);
    c->hud.p_stam.spgbar_size = init_fvect(6, 2.51);
    sfSprite_setScale(c->hud.p_stam.sp_bar_sp, c->hud.p_stam.spbar_size);
    sfSprite_setScale(c->hud.p_stam.sp_gbar_sp, c->hud.p_stam.spgbar_size);
    c->hud.hotbar.bg = new_sprite("sprites/hud/hotbar.png", 1.81, 1.81);
}

void init_player_texture_2(core_t *c)
{
    c->p.player_textures[17] = sfTexture_createFromFile(CLIMB_PATH, NULL);
    c->p.player_textures[18] = sfTexture_createFromFile(DEATH_PATH, NULL);
    c->p.player_textures[19] = sfTexture_createFromFile(HEAL_PATH, NULL);
    c->p.player_textures[20] = NULL;
    for (int i = 0; c->p.player_textures[i]; i++)
        sfTexture_setRepeated(c->p.player_textures[i], sfTrue);
}

void init_player_textures(core_t *c)
{
    c->p.player_textures = malloc(sizeof(sfTexture *) * 21);
    c->p.player_textures[0] = sfTexture_createFromFile(IDLE_PATH, NULL);
    c->p.player_textures[1] = sfTexture_createFromFile(RUN_PATH, NULL);
    c->p.player_textures[2] = sfTexture_createFromFile(JUMP_PATH, NULL);
    c->p.player_textures[3] = sfTexture_createFromFile(FALL_PATH, NULL);
    c->p.player_textures[4] = sfTexture_createFromFile(CROUCH_PATH, NULL);
    c->p.player_textures[5] = sfTexture_createFromFile(ROLL_PATH, NULL);
    c->p.player_textures[6] = sfTexture_createFromFile(PRAY_START_PATH, NULL);
    c->p.player_textures[7] = sfTexture_createFromFile(PRAY_IDLE_PATH, NULL);
    c->p.player_textures[8] = sfTexture_createFromFile(PRAY_END_PATH, NULL);
    c->p.player_textures[9] = sfTexture_createFromFile(HANGING_PATH, NULL);
    c->p.player_textures[10] = sfTexture_createFromFile(STAND_ATCK_PATH, NULL);
    c->p.player_textures[11] = sfTexture_createFromFile(RUN_ATCK_PATH, NULL);
    c->p.player_textures[12] = sfTexture_createFromFile(STAND_ATCK2_PATH, NULL);
    c->p.player_textures[13] = sfTexture_createFromFile(STAND_ATCK3_PATH, NULL);
    c->p.player_textures[14] = sfTexture_createFromFile(FALL_ATCK_PATH, NULL);
    c->p.player_textures[15] = sfTexture_createFromFile(FALL_ATCK2_PATH, NULL);
    c->p.player_textures[16] = sfTexture_createFromFile(JUMP_ATCK_PATH, NULL);
    init_player_texture_2(c);
}
