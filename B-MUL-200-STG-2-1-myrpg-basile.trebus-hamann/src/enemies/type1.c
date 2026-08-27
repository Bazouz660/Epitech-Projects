/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** type1.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void create_health_bar(core_t *c, entity_t *entity)
{
    entity->hb.coutour = sfRectangleShape_create();
    sfRectangleShape_setSize(entity->hb.coutour, init_fvect(130, 7));
    sfRectangleShape_setFillColor(entity->hb.coutour, sfBlack);
    sfRectangleShape_setOutlineColor(entity->hb.coutour, sfBlack);
    sfRectangleShape_setOutlineThickness(entity->hb.coutour, 3);
    entity->hb.red_bar = sfRectangleShape_copy(entity->hb.coutour);
    sfRectangleShape_setOutlineColor(entity->hb.red_bar, sfTransparent);
    sfRectangleShape_setFillColor(entity->hb.red_bar, sfRed);
}

static void type1_b(core_t *c, entity_t *entity, sfVector2f scale)
{
    entity->anim_speed = 0.2;
    sfSprite_setOrigin(entity->sprite, get_sprite_center(entity->sprite));
    sfSprite_setScale(entity->sprite, scale);
    entity->vect.x = 0;
    entity->vect.y = 0;
    entity->health = 150;
    entity->health_mem = entity->health;
    entity->can_be_hit = True;
    entity->hurt_clock = 0;
    entity->anim_state = 0;
    entity->direction = 1;
    entity->attacking = False;
    entity->atk_cooldown = 0;
    entity->atk_cooldown_clock = 0;
    entity->reward_gold = 5;
    entity->reward_xp = 50;
    entity->dmg = 60;
    entity->hit_hitbox = sfRectangleShape_create();
    create_health_bar(c, entity);
}

void create_type1(core_t *c, entity_t *entity, int i)
{
    sfVector2f pos = STAGE.e_spawns[i];
    sfVector2f size = {60, 145};
    sfVector2f scale = {-2.3, 2.3};

    entity->hitbox = sfRectangleShape_create();
    sfRectangleShape_setPosition(entity->hitbox, pos);
    sfRectangleShape_setSize(entity->hitbox, size);
    sfRectangleShape_setFillColor(entity->hitbox, sfRed);
    entity->sprite = sfSprite_create();
    entity->textures = c->en_dic.textures[0];
    sfSprite_setTexture(entity->sprite, entity->textures[0], False);
    init_animated_sprite(entity->sprite, 2, 3);
    entity->pt_frames.x = 2;
    entity->pt_frames.y = 3;
    entity->anim_loop = True;
    entity->frame_index = 0;
    entity->anim_clock = 0;
    type1_b(c, entity, scale);
}
