/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** e_anims.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void choose_anim(core_t *c, enemies_t *node)
{
    if (node->entity.health == 0) {
        e_play_death(c, node);
        return;
    }
    if (node->entity.vect.x != 0) {
        e_play_walk(c, node);
        return;
    }
    if (node->entity.attacking == True) {
        e_play_atk1(c, node);
        return;
    }
    if (node->entity.vect.y == 0 && node->entity.vect.x == 0) {
        e_play_idle(c, node);
        return;
    }
}

static void loop(core_t *c, enemies_t *head)
{
    while (head != NULL) {
        if (head->entity.anim_state == 1
            && head->entity.frame_index == 4 && head->entity.health <= 0)
            delete_enemy(c, head, 1);
        if (head->entity.anim_state != 1 && head->entity.health <= 0)
            sfSound_play(c->audio.t1_death[random_between(0, 3)]);
        choose_anim(c, head);
        head = head->next;
    }
}

void update_e_attack(core_t *c, enemies_t *node)
{
    if (c->clock.seconds > node->entity.atk_cooldown_clock + 0.1) {
        node->entity.atk_cooldown_clock = c->clock.seconds;
        node->entity.atk_cooldown -= 1;
        if (node->entity.atk_cooldown < 0)
            node->entity.atk_cooldown = 0;
    }
    if (node->entity.frame_index == (node->entity.pt_frames.x\
        * node->entity.pt_frames.y)
        && node->entity.attacking == True) {
        node->entity.attacking = False;
        node->entity.atk_cooldown = 5;
    }
    node->entity.anim_clock = c->clock.seconds;
    node->entity.frame_index = \
    upt_anim_sprite(node->entity.sprite,
    node->entity.pt_frames, node->entity.anim_loop,
    node->entity.frame_index);
}

void update_anims_enemy(core_t *c, enemies_t *head)
{
    while (head != NULL) {
        if (c->clock.seconds > head->entity.anim_clock +
            head->entity.anim_speed) {
            update_e_attack(c, head);
        }
        head = head->next;
    }
}

void e_handle_anims(core_t *c)
{
    loop(c, STAGE.e);
}
