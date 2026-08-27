/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** player_anims2.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void play_idle_crouch(core_t *c)
{
    if (c->pst.player_anim_state != 4) {
        c->pst.player_anim_state = 4;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[4], sfTrue);
        init_animated_sprite(c->p.player, 2, 4);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 4;
        c->pst.anim_loop = sfTrue;
    }
}

void play_roll(core_t *c)
{
    if (c->pst.player_anim_state != 5) {
        c->pst.player_anim_state = 5;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[5], sfTrue);
        init_animated_sprite(c->p.player, 2, 2);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 2;
        c->pst.anim_loop = sfTrue;
    }
}

void play_pray_start(core_t *c)
{
    if (c->pst.player_anim_state != 6) {
        c->pst.player_anim_state = 6;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[6], sfTrue);
        init_animated_sprite(c->p.player, 2, 1);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 1;
        c->pst.anim_loop = sfFalse;
    }
}

void play_pray_idle(core_t *c)
{
    if (c->pst.player_anim_state != 7) {
        c->pst.player_anim_state = 7;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[7], sfTrue);
        init_animated_sprite(c->p.player, 2, 8);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 8;
        c->pst.anim_loop = sfTrue;
    }
}

void play_pray_end(core_t *c)
{
    if (c->pst.player_anim_state != 8) {
        c->pst.player_anim_state = 8;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[8], sfTrue);
        init_animated_sprite(c->p.player, 2, 1);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 1;
        c->pst.anim_loop = sfFalse;
    }
}
