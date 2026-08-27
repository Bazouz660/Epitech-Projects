/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** player_anims4.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void play_fall_attack(core_t *c)
{
    if (c->pst.player_anim_state != 14) {
        c->p.stam -= 100;
        c->pst.player_anim_state = 14;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[14], True);
        init_animated_sprite(c->p.player, 3, 1);
        c->p.pt_frames.x = 3;
        c->p.pt_frames.y = 1;
        c->pst.anim_loop = True;
    }
}

void play_fall_attack_2(core_t *c)
{
    if (c->pst.player_anim_state != 15) {
        c->pst.player_anim_state = 15;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[15], True);
        init_animated_sprite(c->p.player, 4, 1);
        c->p.pt_frames.x = 4;
        c->p.pt_frames.y = 1;
        c->pst.anim_loop = False;
    }
}

void play_jump_attack(core_t *c)
{
    if (c->pst.player_anim_state != 16) {
        c->p.stam -= 40;
        c->pst.player_anim_state = 16;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[16], True);
        init_animated_sprite(c->p.player, 3, 1);
        c->p.pt_frames.x = 3;
        c->p.pt_frames.y = 1;
        c->pst.anim_loop = True;
    }
}

void play_climb(core_t *c)
{
    if (c->pst.player_anim_state != 17) {
        c->pst.player_anim_state = 17;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[17], True);
        init_animated_sprite(c->p.player, 2, 3);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 3;
        c->pst.anim_loop = True;
    }
}

void play_death(core_t *c)
{
    if (c->p.health <= 0) {
        if (c->pst.player_anim_state != 18) {
            c->clock.respawn_clock = c->clock.seconds;
            c->pst.atck_mem = False;
            c->p.gold = c->p.gold / 12;
            cancel_hit(c);
            sfSound_play(c->audio.p_death);
            c->pst.player_anim_state = 18;
            c->pst.frame_index = 1;
            sfSprite_setTexture(c->p.player, c->p.player_textures[18], True);
            init_animated_sprite(c->p.player, 2, 2);
            c->p.pt_frames.x = 2;
            c->p.pt_frames.y = 2;
            c->pst.anim_loop = False;
        }
    }
}
