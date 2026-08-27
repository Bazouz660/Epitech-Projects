/*
** EPITECH PROJECT, 2022
** RPG
** File description:
** animate chests
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void animate_chests(core_t *c)
{
    for (int i = 0; STAGE.chests[i].sp; i++) {
        if (STAGE.chests[i].opened == 1 &&
            c->clock.seconds > STAGE.chests[i].anim_clock + 0.1
            && STAGE.chests[i].frame_index < 10) {
            STAGE.chests[i].anim_clock = c->clock.seconds;
            STAGE.chests[i].frame_index = upt_anim_sprite(STAGE.chests[i].sp,
            (sfVector2i){10, 1}, 0, STAGE.chests[i].frame_index);
        }
        if (STAGE.chests[i].opened == 1 && STAGE.chests[i].frame_index > 4
            && sfSprite_getPosition(STAGE.chests[i].loot).y > \
            sfSprite_getPosition(STAGE.chests[i].sp).y - 50
            && c->clock.seconds > STAGE.chests[i].loot_anim_clock + 0.03) {
            STAGE.chests[i].loot_anim_clock = c->clock.seconds;
            set_sprite_pos(STAGE.chests[i].glow,
            sfSprite_getPosition(STAGE.chests[i].loot).x + \
            (sfSprite_getGlobalBounds(STAGE.chests[i].loot).width / 2),
            sfSprite_getPosition(STAGE.chests[i].loot).y + \
            (sfSprite_getGlobalBounds(STAGE.chests[i].loot).height / 2));
            sfSprite_move(STAGE.chests[i].loot, init_fvect(0, -1));
        }
    }
}
