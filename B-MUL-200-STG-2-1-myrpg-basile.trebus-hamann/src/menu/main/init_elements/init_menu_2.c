/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_menu_2.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_menusprite_2(core_t *c)
{
    sfVector2f back_pos = {0, 0};
    sfVector2f play_pos = {1400, 400};
    sfVector2f how_to_play_pos = {1400, 550};
    sfVector2f option_pos = {1400, 700};
    sfVector2f exit_pos = {1400, 850};

    sfSprite_setTexture(c->menu.cursor_s, c->menu.cursor_t, sfTrue);
    sfSprite_setTexture(c->menu.bg_1, c->menu.background_t, sfTrue);
    sfSprite_setTexture(c->menu.button_s[0], c->menu.button_t[0], sfTrue);
    sfSprite_setTexture(c->menu.button_s[1], c->menu.button_t[1], sfTrue);
    sfSprite_setTexture(c->menu.button_s[2], c->menu.button_t[2], sfTrue);
    sfSprite_setPosition(c->menu.bg_1, back_pos);
    sfSprite_setPosition(c->menu.button_s[0], play_pos);
    sfSprite_setPosition(c->menu.button_s[1], option_pos);
    sfSprite_setPosition(c->menu.button_s[2], exit_pos);
    sfSprite_setPosition(c->menu.how_to_play_b, how_to_play_pos);
    init_animated_sprite(c->menu.how_to_play_b, 3, 1);
    sfSprite_setOrigin(c->menu.how_to_play_sp,
    get_sprite_center(c->menu.how_to_play_sp));
    set_sprite_pos(c->menu.how_to_play_sp, 960, 540);
}
