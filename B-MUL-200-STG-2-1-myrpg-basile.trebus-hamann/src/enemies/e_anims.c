/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** e_anims.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void e_play_walk(core_t *c, enemies_t *node)
{
    if (node->entity.anim_state != 0) {
        node->entity.anim_state = 0;
        node->entity.frame_index = 1;
        sfSprite_setTexture(node->entity.sprite, node->entity.textures[0], 1);
        init_animated_sprite(node->entity.sprite, 2, 3);
        sfSprite_setOrigin(node->entity.sprite,
        get_sprite_center(node->entity.sprite));
        node->entity.pt_frames.x = 2;
        node->entity.pt_frames.y = 3;
        node->entity.anim_loop = True;
    }
}

void e_play_death(core_t *c, enemies_t *node)
{
    if (node->entity.anim_state != 1) {
        node->entity.anim_state = 1;
        node->entity.frame_index = 1;
        sfSprite_setTexture(node->entity.sprite, node->entity.textures[1], 1);
        init_animated_sprite(node->entity.sprite, 2, 2);
        sfSprite_setOrigin(node->entity.sprite,
        get_sprite_center(node->entity.sprite));
        node->entity.pt_frames.x = 2;
        node->entity.pt_frames.y = 2;
        node->entity.anim_loop = False;
    }
}

void e_play_idle(core_t *c, enemies_t *node)
{
    if (node->entity.anim_state != 2) {
        node->entity.anim_state = 2;
        node->entity.frame_index = 1;
        sfSprite_setTexture(node->entity.sprite, node->entity.textures[2], 1);
        init_animated_sprite(node->entity.sprite, 2, 2);
        sfSprite_setOrigin(node->entity.sprite,
        get_sprite_center(node->entity.sprite));
        node->entity.pt_frames.x = 2;
        node->entity.pt_frames.y = 2;
        node->entity.anim_loop = True;
    }
}

void e_play_atk1(core_t *c, enemies_t *node)
{
    if (node->entity.anim_state != 3) {
        node->entity.anim_state = 3;
        node->entity.frame_index = 1;
        sfSprite_setTexture(node->entity.sprite, node->entity.textures[3], 1);
        init_animated_sprite(node->entity.sprite, 2, 3);
        sfSprite_setOrigin(node->entity.sprite,
        get_sprite_center(node->entity.sprite));
        node->entity.pt_frames.x = 2;
        node->entity.pt_frames.y = 3;
        node->entity.anim_loop = False;
    }
}
