/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** player_animation.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void animate_attacks_2(core_t *c)
{
    c->pst.run_attack = False;
    if (c->pst.attacking == True && c->mv.global_vect.y == 0
        && c->pst.fall_attack == 0) {
        play_run_attack(c);
        return;
    }
    if (c->pst.attacking == True && c->mv.global_vect.y < 0
        && c->pst.fall_attack == 1) {
        play_fall_attack(c);
        return;
    }
    if (c->pst.fall_attack == 2) {
        play_fall_attack_2(c);
        return;
    }
    if (c->pst.jump_attack == 1) {
        play_jump_attack(c);
        return;
    }
}

void animate_attacks(core_t *c)
{
    if (c->pst.attacking == True && c->mv.global_vect.x == 0
        && c->mv.global_vect.y == 0 && c->pst.fall_attack == 0) {
        if (c->pst.combo == 1) {
            play_stand_attack(c);
            return;
        }
        if (c->pst.combo == 2) {
            play_stand_attack_2(c);
            return;
        }
        if (c->pst.combo == 3) {
            play_stand_attack_3(c);
            return;
        }
        return;
    }
    animate_attacks_2(c);
}

void update_anim(core_t *c)
{
    if (c->clock.seconds > c->clock.player_anim_clock + 0.1) {
        if (c->pst.praying == True)
            c->pst.pray_state++;
        c->clock.player_anim_clock = c->clock.seconds;
        if ((c->pst.combo == 1 && c->pst.frame_index == 3) ||
            (c->pst.run_attack == 1 && (c->pst.frame_index == 4
            || c->pst.frame_index == 8))) {
            c->p.stam -= 40;
            sfSound_play(c->audio.slash_sounds[random_number(0, 3)]);
        }
        c->pst.frame_index = upt_anim_sprite(c->p.player, c->p.pt_frames,
        c->pst.anim_loop, c->pst.frame_index);
    }
}

void update_anim_bs(core_t *c)
{
    if (c->clock.seconds > STAGE.npc[0].anim_bs + 0.17) {
        STAGE.npc[0].anim_bs = c->clock.seconds;
        if (STAGE.npc[0].frame_index_bs == 8)
            sfSound_play(c->audio.anvil[random_number(0, 2)]);
        if (STAGE.npc[0].frame_index_bs == 13) {
            reset_anim(STAGE.npc[0].npc_sp, c);
            STAGE.npc[0].frame_index_bs = 1;
        } else {
            STAGE.npc[0].frame_index_bs = upt_anim_sprite\
            (STAGE.npc[0].npc_sp, STAGE.npc[0].frames_bs,
            STAGE.npc[0].npc_bool, STAGE.npc[0].frame_index_bs);
        }
    }
}

void update_anim_thief(core_t *c)
{
    if (c->clock.seconds > STAGE.npc[1].anim_bs + 0.17) {
        STAGE.npc[1].anim_bs = c->clock.seconds;
        if (STAGE.npc[1].frame_index_bs == 13) {
            reset_anim(STAGE.npc[1].npc_sp, c);
            STAGE.npc[1].frame_index_bs = 1;
        } else {
            STAGE.npc[1].frame_index_bs = upt_anim_sprite\
            (STAGE.npc[1].npc_sp, STAGE.npc[1].frames_bs,
            STAGE.npc[1].npc_bool, STAGE.npc[1].frame_index_bs);
        }
    }
}

void animate_climbing(core_t *c)
{
    if (c->pst.climbing == True)
        play_climb(c);
}

void animate(core_t *c)
{
    e_handle_anims(c);
    animate_chests(c);
    if (c->pst.attacking == False && c->pst.fall_attack == 0
        && c->pst.climbing == False && c->p.health > 0) {
        animate_passive(c);
        animate_passive_2(c);
    }
    animate_climbing(c);
    animate_attacks(c);
    play_death(c);
    update_anims_enemy(c, STAGE.e);
    if (c->scene_status == 3)
        update_anim_bs(c);
    update_anim_thief(c);
    if (c->pst.climbing == False || c->mv.global_vect.y != 0)
        update_anim(c);
    if (c->pst.atck_mem == True && c->pst.player_anim_state == 1) {
        c->pst.atck_mem = False;
        c->pst.frame_index = upt_anim_sprite(c->p.player,
        c->p.pt_frames, c->pst.anim_loop, c->pst.frame_index);
        c->pst.frame_index = upt_anim_sprite(c->p.player,
        c->p.pt_frames, c->pst.anim_loop, c->pst.frame_index);
    }
    handle_states(c);
}
