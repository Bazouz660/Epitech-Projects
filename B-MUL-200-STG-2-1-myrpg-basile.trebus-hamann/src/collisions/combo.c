/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** combo.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void combo_end(core_t *c)
{
    c->pst.attacking = False;
    c->pst.atck_mem = True;
    c->pst.combo = 0;
    if (c->pst.fall_attack == 2)
        c->pst.fall_attack = 0;
}

void reset_enemy_iframes(core_t *c, enemies_t *head)
{
    while (head != NULL) {
        head->entity.can_be_hit = True;
        head = head->next;
    }
}

void handle_combos(core_t *c)
{
    if (((c->pst.frame_index == (c->p.pt_frames.x * c->p.pt_frames.y)
        && c->pst.attacking == True) || (c->pst.combo == 0
        && c->pst.attacking == True && c->mv.global_vect.x == 0))
        && c->pst.fall_attack == 0 && c->pst.jump_attack == False) {
        if (c->pst.combo_next == True && c->pst.combo < 4) {
            c->pst.combo_next = False;
            c->pst.combo++;
        } else {
            if (c->mv.global_vect.x != 0 && c->mv.global_vect.y == 0)
                reset_anim(c->p.player, c);
            combo_end(c);
        }
        reset_enemy_iframes(c, STAGE.e);
    }
}
