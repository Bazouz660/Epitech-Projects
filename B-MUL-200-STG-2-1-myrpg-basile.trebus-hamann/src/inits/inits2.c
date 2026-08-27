/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** inits2.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void init_player_states_3(core_t *c)
{
    c->p.agility = 1;
    c->p.strength = 1;
    c->p.vigor = 1;
    c->p.stam_inv = 1;
    c->p.points = 0;
}

void init_player_states_2(core_t *c)
{
    c->pst.run_attack = False;
    c->pst.climbing = False;
    c->pst.praying = False;
    c->pst.combo_next = False;
    c->pst.can_be_hit = True;
    c->p.exp = 0;
    c->p.exp_buff = 0;
    c->p.level = 1;
    c->pst.frame_index = 1;
    c->pst.combo = 0;
    c->p.dmg = 20;
    c->pst.fall_attack = 0;
    c->pst.combo = 0;
    c->p.health = 500;
    c->p.health_mem = c->p.health;
    c->p.stam = 500;
    c->p.stam_max = c->p.stam;
    c->p.hit_hitbox = sfRectangleShape_create();
    init_player_states_3(c);
}

void init_player_states(core_t *c)
{
    c->pst.sprinting = False;
    c->pst.atck_mem = False;
    c->pst.can_grab = False;
    c->pst.moving = False;
    c->pst.rolling = False;
    c->pst.roll_enabled = True;
    c->pst.hanging = False;
    c->pst.pray_end = False;
    c->pst.sliding = False;
    c->pst.attacking = False;
    c->pst.falling = True;
    c->pst.jumping = True;
    c->pst.crouching = False;
    c->pst.memcrouching = False;
    c->clock.p_hurt_cooldown = 0;
    c->pst.jump_attack = 0;
    c->pst.p_direction = -1;
    c->pst.player_anim_state = 0;
    init_player_states_2(c);
}
