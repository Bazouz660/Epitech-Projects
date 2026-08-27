/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** handle_anim_states.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void handle_states(core_t *c)
{
    handle_combos(c);
    handle_fall_atk(c);
    handle_jump_atk(c);
    handle_run_attack(c);
}

void handle_fall_atk(core_t *c)
{
    if (c->pst.frame_index == (c->p.pt_frames.x * c->p.pt_frames.y)
        && c->pst.fall_attack == 2) {
        combo_end(c);
    }
    if (c->pst.fall_attack == 1 && c->pst.grounded == True) {
        sfSound_play(c->audio.fall_atck_impact);
        c->pst.fall_attack = 2;
    }
}

void handle_run_attack(core_t *c)
{
    if (c->pst.run_attack == True && !sfKeyboard_isKeyPressed(c->keys.left)
        && !sfKeyboard_isKeyPressed(c->keys.right)) {
        c->pst.attacking = False;
        c->pst.run_attack = False;
        c->keys.can_click = True;
        c->pst.combo = 0;
        c->pst.combo_next = False;
        c->pst.atck_mem = True;
    }
}

void handle_jump_atk(core_t *c)
{
    if (c->pst.jump_attack == 1 && c->mv.global_vect.y <= 0) {
        c->pst.attacking = False;
        c->pst.jump_attack = False;
        c->pst.combo = 0;
        c->pst.combo_next = False;
        c->pst.atck_mem = True;
        reset_enemy_iframes(c, STAGE.e);
        c->pst.jump_attack = 2;
    }
    if (c->pst.grounded == True && c->pst.jump_attack == 2)
        c->pst.jump_attack = 0;
}

void hanging_handler(core_t *c)
{
    if ((sfKeyboard_isKeyPressed(c->keys.right)
        || sfKeyboard_isKeyPressed(c->keys.left))
        && c->pst.can_grab == True && c->mv.global_vect.y <= 0
        && c->pst.grounded == False) {
        c->mv.global_vect.y = 0;
        c->pst.hanging = True;
        if (sfKeyboard_isKeyPressed(c->keys.jump)) {
            c->pst.jumping = True;
            c->mv.global_vect.y = 17;
            c->mv.acceleration = 0;
        }
    } else
        c->pst.hanging = False;
}
