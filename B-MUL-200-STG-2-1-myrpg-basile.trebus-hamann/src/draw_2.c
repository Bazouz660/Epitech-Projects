/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** draw_2.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void update_saving_clock(core_t *c)
{
    sfColor color = sfSprite_getColor(c->p_saved);

    if (c->clock.seconds > c->clock.saving_clock + 4.0 && c->saving > 0) {
        c->saving++;
        c->clock.saving_clock = c->clock.seconds;
    }
    if (c->saving == 2 && color.a <= 0) {
        c->saving = 0;
        color.a = 0;
        c->color.fade_in.a = 0;
        sfSprite_setColor(c->p_saved, color);
    }
}

void draw_enemies(core_t *c, enemies_t *head)
{
    while (head != NULL) {
        sfRenderWindow_drawSprite(c->window, head->entity.sprite, NULL);
        sfRenderWindow_drawRectangleShape(c->window, head->entity.hb.coutour, NULL);
        sfRenderWindow_drawRectangleShape(c->window, head->entity.hb.red_bar, NULL);
        head = head->next;
    }
}

void draw_hud(core_t *c)
{
    sfRenderWindow_drawSprite(c->window, c->hud.p_health.sp_bar_hpp, NULL);
    sfRenderWindow_drawSprite(c->window, c->hud.p_health.sp_rbar_hpp, NULL);
    sfRenderWindow_drawSprite(c->window, c->hud.p_stam.sp_bar_sp, NULL);
    sfRenderWindow_drawSprite(c->window, c->hud.p_stam.sp_gbar_sp, NULL);
    sfRenderWindow_drawSprite(c->window, c->hud.hotbar.bg, NULL);
    sfRenderWindow_drawSprite(c->window, c->hud.inv_prom.bg, NULL);
    sfRenderWindow_drawSprite(c->window, c->hud.hotbar.i_a, NULL);
    sfRenderWindow_drawSprite(c->window, c->hud.hotbar.i_b, NULL);
    sfRenderWindow_drawSprite(c->window, c->hud.hotbar.i_c, NULL);
    sfRenderWindow_drawText(c->window, c->hud.inv_prom.key, NULL);
}

void draw_particles_loop(core_t *c)
{
    sfFloatRect rect1 = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfFloatRect rect2;

    for (int i = 0; STAGE.campfires[i].lit != -1; i++) {
        rect2 = sfSprite_getGlobalBounds(STAGE.campfires[i].sprite);
        sfRenderWindow_drawSprite(c->window, STAGE.campfires[i].sprite, NULL);
        if (sfFloatRect_intersects(&rect1, &rect2, NULL) && c->saving == 0) {
            set_sprite_pos(STAGE.campfires[i].key_prompt,
            rect2.left + 70, rect2.top - 50);
            sfRenderWindow_drawSprite(c->window, STAGE.campfires[i].key_prompt,
            NULL);
        }
        if (STAGE.campfires[i].lit == True) {
            c->paused == 0 ? animate_light(c,
            STAGE.campfires[i].center_point) : 0;
            draw_particles(c, STAGE.campfires[i].particles->part_head,
            STAGE.campfires[i].particles->part_head);
        }
    }
}

void draw_aura(core_t *c)
{
    for (int i = 0; STAGE.campfires[i].lit != -1; i++)
        if (STAGE.campfires[i].lit == True)
            sfRenderWindow_drawVertexArray(c->window,
            STAGE.campfires[i].aura, NULL);
}
