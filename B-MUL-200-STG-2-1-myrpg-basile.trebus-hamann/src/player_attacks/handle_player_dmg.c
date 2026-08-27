/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** handle_player_dmg.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void player_dmg_loop(core_t *c, enemies_t *head)
{
    sfFloatRect rect1 = sfRectangleShape_getGlobalBounds(c->p.hit_hitbox);
    sfFloatRect rect2;

    while (head != NULL) {
        rect2 = sfRectangleShape_getGlobalBounds(head->entity.hitbox);
        if (sfFloatRect_intersects(&rect1, &rect2, NULL)
            && head->entity.can_be_hit == True && head->entity.health > 0) {
            head->entity.hurt_clock = c->clock.seconds;
            sfSprite_setColor(head->entity.sprite, sfRed);
            head->entity.health -= c->p.dmg;
            sfSound_play(c->audio.t1_hurt);
            if (head->entity.health < 0)
                head->entity.health = 0;
            head->entity.can_be_hit = False;
        } else if (c->clock.seconds > head->entity.hurt_clock + 0.5) {
            head->entity.hurt_clock = c->clock.seconds;
            sfSprite_setColor(head->entity.sprite, sfWhite);
        }
        head = head->next;
    }
}

void handle_enemies_health(core_t *c, enemies_t *head)
{
    sfVector2f scale;

    while (head != NULL) {
        scale = sfRectangleShape_getScale(head->entity.hb.red_bar);
        scale.x = (head->entity.health * 100 / head->entity.health_mem) / 100;
        sfRectangleShape_setScale(head->entity.hb.red_bar, scale);
        if (head->entity.health <= 0 && head->entity.vect.y == 0)
            head->entity.vect.x = 0;
        head = head->next;
    }
}

void handle_player_dmg(core_t *c)
{
    player_dmg_loop(c, STAGE.e);
    handle_enemies_health(c, STAGE.e);
    if (c->pst.attacking == False)
        reset_enemy_iframes(c, STAGE.e);
}
