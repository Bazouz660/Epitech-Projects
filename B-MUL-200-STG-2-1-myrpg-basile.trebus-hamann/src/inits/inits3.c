/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** inits3.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_colors(core_t *c)
{
    c->color.fade_out = sfColor_fromRGBA(0, 0, 0, 255);
    c->color.fade_in = sfColor_fromRGBA(255, 255, 255, 0);
    c->color.light_color = sfColor_fromRGBA(255, 195, 0, 50);
    c->color.transparent_red = sfColor_fromRGBA(255, 0, 0, 100);
}

void init_defaut_sprites(core_t *c)
{
    init_enemies_textures(c);
    c->door_bg = new_sprite("sprites/door_bg.png", 3.01, 3.01);
    c->hud.inv_prom.bg = new_sprite("sprites/inv_prompt.png", 0.2, 0.2);
    c->p_menu.bg = new_sprite("sprites/pause_menu.png", 1, 1);
    c->background = new_sprite("sprites/background/background.jpg", 1, 1);
    c->black_layer = new_sprite("sprites/background/black.jpg", 10, 10);
    c->you_died = new_sprite("sprites/you_died.png", 1, 1);
    c->p_saved = new_sprite("sprites/progress_saved.png", 1, 1);
    c->p.player_hitbox = new_sprite("sprites/debug.jpg", 0.30, 0.48);
    c->p.player = new_sprite("sprites/player/idle.png", 3, 3);
    c->shop.shop_s = new_sprite("sprites/shop.png", 2.3, 2.3);
    sfSprite_setColor(c->p_saved, (sfColor){255, 255, 255, 0});
    sfSprite_setColor(c->you_died, (sfColor){255, 255, 255, 0});
    set_sprite_pos(c->background, 0, 1000);
    set_sprite_pos(c->black_layer, -1000, -1000);
    sfSprite_setOrigin(c->you_died, get_sprite_center(c->you_died));
    sfSprite_setOrigin(c->p_saved, get_sprite_center(c->p_saved));
    sfSprite_setOrigin(c->p_menu.bg, get_sprite_center(c->p_menu.bg));
}
