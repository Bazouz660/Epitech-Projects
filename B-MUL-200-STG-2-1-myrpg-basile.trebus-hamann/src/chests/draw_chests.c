/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** draw_chests.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void draw_chests(core_t *c)
{
    sfFloatRect rect1 = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfFloatRect rect2;

    for (int i = 0; STAGE.chests[i].sp; i++) {
        rect2 = sfSprite_getGlobalBounds(STAGE.chests[i].sp);
        sfRenderWindow_drawSprite(c->window, STAGE.chests[i].sp, NULL);
        if (sfFloatRect_intersects(&rect1, &rect2, NULL)
            && (STAGE.chests[i].opened == 0
            || sfSprite_getPosition(STAGE.chests[i].loot).y <= \
            sfSprite_getPosition(STAGE.chests[i].sp).y - 50)
            && STAGE.chests[i].empty == 0)
            sfRenderWindow_drawSprite(c->window, STAGE.chests[i].prompt, NULL);
        if (STAGE.chests[i].opened == 1 && STAGE.chests[i].frame_index > 4
            && STAGE.chests[i].empty == 0) {
            sfRenderWindow_drawSprite(c->window, STAGE.chests[i].glow, NULL);
            sfRenderWindow_drawSprite(c->window, STAGE.chests[i].loot, NULL);
        }
        if (STAGE.chests[i].opened == 1 && STAGE.chests[i].frame_index > 4 &&
            sfSprite_getPosition(STAGE.chests[i].loot).y > \
            sfSprite_getPosition(STAGE.chests[i].sp).y - 50)
            fade_in(c, STAGE.chests[i].loot);
            fade_in(c, STAGE.chests[i].glow);
    }
}
