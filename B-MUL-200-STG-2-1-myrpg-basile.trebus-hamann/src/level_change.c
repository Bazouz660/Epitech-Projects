/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** level_change.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void next_level(core_t *c, sfFloatRect rect1)
{
    if (c->stage_index == 0) {
        sfSprite_setColor(c->black_layer, sfBlack);
        set_sprite_pos(c->p.player_hitbox, 825, 2785);
        set_sprite_pos(c->background, 0, 2785);
        c->save.last_camp = sfSprite_getPosition(c->p.player_hitbox);
        init_stage_1(c);
        return;
    }
    if (c->stage_index == 1) {
        sfSprite_setColor(c->black_layer, sfBlack);
        set_sprite_pos(c->p.player_hitbox, 825, 2785);
        c->save.last_camp = sfSprite_getPosition(c->p.player_hitbox);
        init_stage_2(c);
        return;
    }
    if (c->stage_index == 2) {
        sfSprite_setColor(c->black_layer, sfBlack);
        set_sprite_pos(c->p.player_hitbox, -1222, 2552);
        set_sprite_pos(c->background, -3000, 2552);
        c->save.last_camp = sfSprite_getPosition(c->p.player_hitbox);
        init_stage_3(c);
        return;
    }
}

static void prev_level(core_t *c, sfFloatRect rect1)
{
    if (c->stage_index == 1) {
        sfSprite_setColor(c->black_layer, sfBlack);
        set_sprite_pos(c->p.player_hitbox, 6150, 560);
        set_sprite_pos(c->background, 4700, 560);
        init_stage_0(c);
        return;
    } else if (c->stage_index == 2) {
        sfSprite_setColor(c->black_layer, sfBlack);
        set_sprite_pos(c->p.player_hitbox, 4685, -377);
        set_sprite_pos(c->background, 4600, -377);
        init_stage_1(c);
        return;
    }
    if (c->stage_index == 3) {
        sfSprite_setColor(c->black_layer, sfBlack);
        set_sprite_pos(c->p.player_hitbox, 4011, -807);
        set_sprite_pos(c->background, 2000, -377);
        init_stage_2(c);
        return;
    }
}

void handle_lvl_change(core_t *c)
{
    sfFloatRect rect1 = sfSprite_getGlobalBounds(c->p.player_hitbox);

    if (sfFloatRect_contains(&STAGE.exit_rect, rect1.left + (rect1.width / 2),
        rect1.top + (rect1.height / 2)))
        next_level(c, rect1);
    else if (sfFloatRect_contains(&STAGE.entry_rect,
        rect1.left + (rect1.width / 2), rect1.top + (rect1.height / 2)))
        prev_level(c, rect1);
}
