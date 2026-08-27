/*
** EPITECH PROJECT, 2022
** fsqfsqfsqf
** File description:
** fsqfsq
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_leave_settings(core_t *c)
{
    sfVector2f pos = {50, 900};

    c->option.leave_rect.height = 105;
    c->option.leave_rect.width = 420;
    c->option.leave_s = sfSprite_create();
    c->option.leave_t = sfTexture_createFromFile(BUTTON_LEAVE_PATH, NULL);
    sfSprite_setPosition(c->option.leave_s, pos);
    sfSprite_setTexture(c->option.leave_s, c->option.leave_t, sfTrue);
}

void init_optiontextures(core_t *c)
{
    c->option.fps_texture = malloc (sizeof(sfTexture*) * 4);
    c->option.fps_texture[0] = sfTexture_createFromFile(BUTTON_30FPS_PATH, NULL);
    c->option.fps_texture[1] = sfTexture_createFromFile(BUTTON_60FPS_PATH, NULL);
    c->option.fps_texture[2] = sfTexture_createFromFile(BUTTON_90FPS_PATH, NULL);
    c->option.fps_texture[3] = sfTexture_createFromFile(BUTTON_120FPS_PATH, NULL);
}

void init_optionsprites(core_t *c)
{
    sfVector2f pos1 = {600, 200};
    sfVector2f pos2 = {1150, 200};
    sfVector2f pos3 = {600, 350};
    sfVector2f pos4 = {1150, 350};

    c->option.fps_sprite = malloc(sizeof(sfSprite *) * 4);
    c->option.fps_sprite[0] = sfSprite_create();
    c->option.fps_sprite[1] = sfSprite_create();
    c->option.fps_sprite[2] = sfSprite_create();
    c->option.fps_sprite[3] = sfSprite_create();
    sfSprite_setTexture(c->option.fps_sprite[0], c->option.fps_texture[0], sfTrue);
    sfSprite_setTexture(c->option.fps_sprite[1], c->option.fps_texture[1], sfTrue);
    sfSprite_setTexture(c->option.fps_sprite[2], c->option.fps_texture[2], sfTrue);
    sfSprite_setTexture(c->option.fps_sprite[3], c->option.fps_texture[3], sfTrue);
    sfSprite_setPosition(c->option.fps_sprite[0], pos1);
    sfSprite_setPosition(c->option.fps_sprite[1], pos2);
    sfSprite_setPosition(c->option.fps_sprite[2], pos3);
    sfSprite_setPosition(c->option.fps_sprite[3], pos4);
}

void init_fpsrect(core_t *c)
{
    c->option.button_rect = malloc(sizeof(sfIntRect) * 4);
    c->option.button_rect[0].width = 420;
    c->option.button_rect[0].height = 105;
    c->option.button_rect[1].width = 420;
    c->option.button_rect[1].height = 105;
    c->option.button_rect[2].width = 420;
    c->option.button_rect[2].height = 105;
    c->option.button_rect[3].width = 420;
    c->option.button_rect[3].height = 105;
}

void init_option(core_t *c)
{
    init_optiontextures(c);
    init_leave_settings(c);
    init_optionsprites(c);
    init_fpsrect(c);
    init_sound(c);
}