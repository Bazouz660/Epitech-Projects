/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** mouse_inputs.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void combo_input(core_t *c)
{
    c->keys.can_click = False;
    if (c->pst.combo == 1) {
        c->pst.combo_next = True;
    } else if (c->pst.combo == 2)
        c->pst.combo_next = True;
}

void jump_attack_input(core_t *c)
{
    sfSound_play(c->audio.slash_sounds[random_number(0, 3)]);
    c->mv.global_vect.y < 17 ? c->mv.global_vect.y = 17 : 0;
    c->pst.jump_attack = 1;
    c->mv.global_vect.x = 10 * c->pst.p_direction;
    c->pst.attacking = True;
}

void fall_attack_input(core_t *c)
{
    c->mv.global_vect.y > -10 ? c->mv.global_vect.y = -10 : 0;
    c->pst.fall_attack = 1;
    c->mv.global_vect.x = 0;
    c->pst.attacking = True;
}

void mouse_inputs(core_t *c)
{
    if (sfMouse_isButtonPressed(sfMouseLeft) && c->pst.attacking == False
        && c->pst.combo == 0 && c->pst.rolling == False) {
        c->keys.can_click = False;
        if (c->pst.grounded == False && sfKeyboard_isKeyPressed(c->keys.down)
            && c->p.stam >= 100) {
            fall_attack_input(c);
            return;
        }
        if (c->pst.grounded == False && sfKeyboard_isKeyPressed(c->keys.up)
            && c->pst.jump_attack == 0 && c->p.stam >= 40) {
            jump_attack_input(c);
            return;
        }
        if (c->pst.fall_attack == 0 && c->pst.grounded == True
            && c->p.stam >= 40) {
            c->pst.combo_next = True;
            c->pst.attacking = True;
            return;
        }
    } else if (sfMouse_isButtonPressed(sfMouseLeft) && c->pst.attacking == True
        && c->p.stam >= 40)
        combo_input(c);
}
