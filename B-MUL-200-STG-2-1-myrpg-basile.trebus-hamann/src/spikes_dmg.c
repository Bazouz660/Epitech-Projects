/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** spikes_dmg.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void handle_spikes_dmg_p(core_t *c)
{
    sfFloatRect rect1 = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfFloatRect rect2;

    for (int i = 0; i < STAGE.spikes_nb; i++) {
        rect2 = sfSprite_getGlobalBounds(STAGE.spikes[i]);
        if (sfFloatRect_intersects(&rect1, &rect2, NULL) && c->p.health > 0
            && c->pst.can_be_hit == True) {
            sfSound_play(c->p.hurt_sound[random_between(0, 3)]);
            sfSprite_setColor(c->p.player, sfRed);
            c->pst.can_be_hit = False;
            c->clock.p_hurt_cooldown = c->clock.seconds;
            c->p.health -= 70;
        }
        if (sfFloatRect_intersects(&rect1, &rect2, NULL))
            c->mv.global_vect.x *= 0.2;
    }
}

void e_spikes_dmg_loop(core_t *c, enemies_t *head, sfFloatRect rect1)
{
    sfFloatRect rect2;

    while (head != NULL) {
        rect2 = sfRectangleShape_getGlobalBounds(head->entity.hitbox);
        if (sfFloatRect_intersects(&rect1, &rect2, NULL)
            && head->entity.can_be_hit == True && head->entity.health > 0) {
            head->entity.hurt_clock = c->clock.seconds;
            sfSprite_setColor(head->entity.sprite, sfRed);
            head->entity.health -= 70;
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

void handle_spikes_dmg_e(core_t *c, enemies_t *head)
{
    sfFloatRect rect1;

    for (int i = 0; i < STAGE.spikes_nb; i++) {
        rect1 = sfSprite_getGlobalBounds(STAGE.spikes[i]);
        e_spikes_dmg_loop(c, head, rect1);
    }
}
