/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** handle_dmg.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void handle_enemies_dmg(core_t *c, enemies_t *head)
{
    sfFloatRect rect1 = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfFloatRect rect2;

    while (head != NULL) {
        rect2 = sfRectangleShape_getGlobalBounds(head->entity.hit_hitbox);
        if (sfFloatRect_intersects(&rect1, &rect2, NULL) && c->p.health > 0
            && c->pst.can_be_hit == True) {
            sfSound_play(c->p.hurt_sound[random_between(0, 3)]);
            sfSprite_setColor(c->p.player, sfRed);
            c->pst.can_be_hit = False;
            c->clock.p_hurt_cooldown = c->clock.seconds;
            c->p.health -= head->entity.dmg / \
            (1 + c->item[c->inventory.slots[17].id].stats.armor);
        }
        head = head->next;
    }
}

void update_health_bar(core_t *c)
{
    sfVector2f scale = sfSprite_getScale(c->hud.p_health.sp_bar_hpp);

    scale.x = scale.x * (c->p.health / c->p.health_mem);
    if (scale.x < 0)
        scale.x = 0;
    sfSprite_setScale(c->hud.p_health.sp_rbar_hpp, scale);
}

void update_hurt_cooldown(core_t *c)
{
    if (c->clock.seconds > c->clock.p_hurt_cooldown + 0.2) {
        c->pst.can_be_hit = True;
        sfSprite_setColor(c->p.player, sfWhite);
    }
    if (c->pst.rolling == True)
        c->pst.can_be_hit = False;
}

void handle_dmg(core_t *c)
{
    handle_spikes_dmg_p(c);
    handle_spikes_dmg_e(c, STAGE.e);
    handle_player_dmg(c);
    handle_enemies_dmg(c, STAGE.e);
    update_health_bar(c);
    update_hurt_cooldown(c);
    if (c->p.health <= 0) {
        c->mv.global_vect.x = 0;
        c->pst.attacking = False;
        c->pst.fall_attack = 0;
    }
}
