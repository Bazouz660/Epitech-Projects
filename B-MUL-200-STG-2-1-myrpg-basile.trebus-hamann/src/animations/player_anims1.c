/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** player_anims1.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void play_idle(core_t *c)
{
    if (c->pst.player_anim_state != 0) {
        c->pst.player_anim_state = 0;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[0], True);
        init_animated_sprite(c->p.player, 2, 4);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 4;
        c->pst.anim_loop = True;
    }
}

void play_jump(core_t *c)
{
    if (c->pst.player_anim_state != 2) {
        c->pst.player_anim_state = 2;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[2], True);
        init_animated_sprite(c->p.player, 2, 2);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 2;
        c->pst.anim_loop = False;
    }
}

void play_run(core_t *c)
{
    if (c->pst.player_anim_state != 1) {
        c->pst.player_anim_state = 1;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[1], True);
        init_animated_sprite(c->p.player, 2, 4);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 4;
        c->pst.anim_loop = True;
    }
}

void play_fall(core_t *c)
{
    if (c->pst.player_anim_state != 3) {
        c->pst.player_anim_state = 3;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[3], True);
        init_animated_sprite(c->p.player, 2, 4);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 4;
        c->pst.anim_loop = False;
    }
}
