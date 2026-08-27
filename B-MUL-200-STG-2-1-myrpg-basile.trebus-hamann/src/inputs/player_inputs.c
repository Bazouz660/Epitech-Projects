/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** player_inputs.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void cancel_hit(core_t *c)
{
    c->pst.attacking = False;
    c->keys.can_click = True;
    c->pst.combo = 0;
    c->pst.combo_next = False;
    c->pst.atck_mem = True;
    sfRectangleShape_setSize(c->p.hit_hitbox, init_fvect(0, 0));
}

void side_jump(core_t *c)
{
    if (c->pst.sliding == True && c->pst.grounded == False
        && c->clock.seconds > c->clock.side_jump_clock + 0.5) {
        c->mv.global_vect.x = 6 * (-c->pst.p_direction);
        c->pst.side_jumping = True;
        inv_player_direction(c);
        c->pst.player_anim_state = 0;
        c->clock.side_jump_clock = c->clock.seconds;
        sfSound_play(c->audio.landing_sound);
        cancel_hit(c);
        c->pst.jumping = True;
        c->mv.global_vect.y = 17;
        c->mv.acceleration = 0;
    }
}

void jump_input(core_t *c)
{
    if ((sfKeyboard_isKeyPressed(c->keys.jump) && c->pst.jumping == False
        && c->pst.crouching == False && c->pst.memcrouching == False
        && c->pst.praying == False) && c->pst.falling == False
        && (c->pst.sliding == True || c->pst.grounded == True)) {
        if (c->pst.sliding == True && c->mv.global_vect.y > 0
            && c->pst.grounded == False)
            c->pst.falling = True;
        if (c->pst.grounded == True) {
            cancel_hit(c);
            c->pst.jumping = True;
            c->mv.global_vect.y = 17;
            c->mv.acceleration = 0;
            return;
        }
        side_jump(c);
    } else if (c->pst.jumping == False)
        c->pst.falling = True;
    if ((c->pst.sliding == False && c->pst.grounded == False)) {
        c->pst.falling = True;
        c->pst.jumping = False;
    }
}

void handle_sprint(core_t *c)
{
    if (sfKeyboard_isKeyPressed(c->keys.sprint) && c->pst.grounded == True
        && c->pst.moving == True) {
        c->pst.sprinting = True;
    } else if (!sfKeyboard_isKeyPressed(c->keys.sprint)
        && c->pst.grounded == True)
        c->pst.sprinting = False;
    if ((c->pst.sprinting == True && c->pst.moving == True)
        || c->pst.rolling == True) {
        c->mv.global_vect.x = (c->p.player_speed * 1.5) * c->pst.p_direction;
        if (c->pst.rolling == True)
            c->mv.global_vect.x = (c->p.player_speed * 2) * c->pst.p_direction;
    }
}

void player_inputs(core_t *c)
{
    if (c->keys.can_click == True && c->pst.hanging == False
        && c->pst.praying == False)
        mouse_inputs(c);
    if (c->pst.fall_attack == 0 && c->pst.jump_attack != 1) {
        direction_handler(c);
        handle_sprint(c);
        handle_crouch(c);
        jump_input(c);
    }
    if (c->clock.seconds > c->clock.side_jump_clock + 0.5
        && c->pst.side_jumping == True) {
        c->clock.seconds > c->clock.side_jump_clock;
        c->pst.side_jumping = False;
    }
}
