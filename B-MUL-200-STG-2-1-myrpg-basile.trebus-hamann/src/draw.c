/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** draw.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void draw_map(core_t *c)
{
    for (int i = 0; i < 5; i++) {
        sfRenderWindow_drawVertexArray(c->window, c->map.m_floor[i].walls[0],
        &c->map.f_state);
        sfRenderWindow_drawVertexArray(c->window, c->map.m_floor[i].walls[1],
        &c->map.f_state);
        sfRenderWindow_drawVertexArray(c->window, c->map.m_floor[i].walls[2],
        &c->map.w_state);
        if (c->map.m_floor[i].walls[3]) {
            sfRenderWindow_drawVertexArray(c->window,
            c->map.m_floor[i].walls[3], &c->map.w_state);
        }
    }
}

static void progress_saved(core_t *c)
{
    if (c->saving == 1)
        fade_in(c, c->p_saved);
    if (c->saving == 2)
        fade_out(c, 0.05, 0.01, c->p_saved);
    if (c->saving > 0)
        sfRenderWindow_drawSprite(c->window, c->p_saved, NULL);
    update_saving_clock(c);
}

static void draw_spikes(core_t *c)
{
    for (int i = 0; i < STAGE.spikes_nb; i++) {
        sfRenderWindow_drawSprite(c->window, STAGE.spikes[i], NULL);
    }
}

static void render_death_msg(core_t *c)
{
    if (c->p.health <= 0) {
        fade_in(c, c->you_died);
        sfRenderWindow_drawSprite(c->window, c->you_died, NULL);
    }
}

static void draw_npcs(core_t *c)
{
    if (c->stage_index == 0)
        for (int i = 1; STAGE.npc[i].npc_sp; i++)
            sfRenderWindow_drawSprite(c->window, STAGE.npc[i].npc_sp, NULL);
}

void draw_scene(core_t *c)
{
    fade_out(c, 0.05, 0.01, c->black_layer);
    sfRenderWindow_clear(c->window, sfBlack);
    sfRenderWindow_drawSprite(c->window, c->background, NULL);
    if (c->stage_index == 2 || c->stage_index == 3)
        sfRenderWindow_drawSprite(c->window, c->door_bg, NULL);
    if (c->stage_index == 0) {
        sfRenderWindow_drawSprite(c->window, c->shop.shop_s, NULL);
    }
    draw_chests(c);
    for (int i = 0; STAGE.la[i].ladder; i++)
        sfRenderWindow_drawRectangleShape(c->window, STAGE.la[i].ladder, NULL);
    draw_particles_loop(c);
    draw_enemies(c, STAGE.e);
    sfRenderWindow_drawSprite(c->window, c->p.player, NULL);
    draw_spikes(c);
    draw_aura(c);
    sfRenderWindow_drawSprite(c->window, STAGE.bg, NULL);
    draw_hud(c);
    draw_npcs(c);
    if (c->stage_index == 0)
        render_dialogue(c);
    render_inventory(c);
    event_shop(c);
    sfRenderWindow_drawSprite(c->window, c->black_layer, NULL);
    progress_saved(c);
    render_death_msg(c);
    if (c->paused == 1)
        render_pause_menu(c);
}
