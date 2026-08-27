/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** player_anims3.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void play_hanging(core_t *c)
{
    c->p.player_pos.x += (sfSprite_getGlobalBounds(c->p.player_hitbox).width \
    / 2) - (23 * c->pst.p_direction);
    if (c->pst.player_anim_state != 9) {
        c->pst.player_anim_state = 9;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[9], sfTrue);
        init_animated_sprite(c->p.player, 2, 4);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 4;
        c->pst.anim_loop = True;
    }
}

void play_stand_attack(core_t *c)
{
    if (c->pst.player_anim_state != 10) {
        c->p.stam -= 40;
        c->pst.player_anim_state = 10;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[10], True);
        init_animated_sprite(c->p.player, 7, 1);
        c->p.pt_frames.x = 7;
        c->p.pt_frames.y = 1;
        c->pst.anim_loop = False;
    }
}

void play_run_attack(core_t *c)
{
    c->pst.run_attack = True;
    if (c->pst.player_anim_state != 11) {
        c->pst.player_anim_state = 11;
        c->pst.frame_index = 1;
        sfSprite_setTexture(c->p.player, c->p.player_textures[11], True);
        init_animated_sprite(c->p.player, 2, 5);
        c->p.pt_frames.x = 2;
        c->p.pt_frames.y = 5;
        c->pst.anim_loop = False;
    }
}

void play_stand_attack_2(core_t *c)
{
    if (c->pst.player_anim_state != 12) {
        c->p.stam -= 40;
        c->pst.player_anim_state = 12;
        c->pst.frame_index = 1;
        sfSound_play(c->audio.slash_sounds[random_number(0, 3)]);
        sfSprite_setTexture(c->p.player, c->p.player_textures[12], True);
        init_animated_sprite(c->p.player, 3, 1);
        c->p.pt_frames.x = 3;
        c->p.pt_frames.y = 1;
        c->pst.anim_loop = False;
    }
}

void play_stand_attack_3(core_t *c)
{
    if (c->pst.player_anim_state != 13) {
        c->p.stam -= 40;
        c->pst.player_anim_state = 13;
        c->pst.frame_index = 1;
        sfSound_play(c->audio.slash_sounds[random_number(0, 3)]);
        sfSprite_setTexture(c->p.player, c->p.player_textures[13], True);
        init_animated_sprite(c->p.player, 4, 1);
        c->p.pt_frames.x = 4;
        c->p.pt_frames.y = 1;
        c->pst.anim_loop = False;
    }
}
