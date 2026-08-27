/*
** EPITECH PROJECT, 2022
** fsqfsfsqf
** File description:
** sqfsqf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_menutxt(core_t *c)
{
    sfVector2f title_pos = {1250, 40};
    sfColor grey = sfColor_fromRGB(75, 13, 0);

    c->menu.rpg_title = sfText_create();
    c->menu.title_font = sfFont_createFromFile("./misc/ds.ttf");
    sfText_setString(c->menu.rpg_title, "");
    sfText_setFont(c->menu.rpg_title, c->menu.title_font);
    sfText_setCharacterSize(c->menu.rpg_title, 120);
    sfText_setColor(c->menu.rpg_title, grey);
    sfText_setPosition(c->menu.rpg_title, title_pos);
}

void init_menutexture(core_t *c)
{
    c->menu.button_t = malloc(sizeof(sfTexture *) * 3);
    c->menu.background_t = sfTexture_createFromFile(MENU_BACKGROUND,NULL);
    c->menu.button_t[0] = sfTexture_createFromFile(BUTTON_PLAY_PATH, NULL);
    c->menu.button_t[1] = sfTexture_createFromFile(BUTTON_OPTION_PATH, NULL);
    c->menu.button_t[2] = sfTexture_createFromFile(BUTTON_EXIT_PATH, NULL);
    c->menu.cursor_t = sfTexture_createFromFile("./sprites/cursor.png", NULL);
}

void init_menusprite(core_t *c)
{
    sfVector2f origin = {50, -10};

    c->menu.button_s = malloc(sizeof(sfSprite*) * 3);
    c->menu.button_s[0] = sfSprite_create();
    c->menu.button_s[1] = sfSprite_create();
    c->menu.button_s[2] = sfSprite_create();
    c->menu.cursor_s = sfSprite_create();
    c->menu.bg_1 = sfSprite_create();
    c->menu.how_to_play_b = new_sprite("sprites/button/how_to_play_b.png",
    1, 1);
    c->menu.how_to_play_sp = new_sprite("sprites/how_to_play.png", 1, 1);
    init_menusprite_2(c);
    c->menu.embers = new_sprite("sprites/background/embers.png", 1, 1);
    c->menu.bg_2 = new_sprite("sprites/background/char.png", 1, 1);
    c->menu.bg_3 = new_sprite("sprites/background/title.png", 1, 1);
    c->menu.bg_4 = new_sprite("sprites/background/smoke.png", 1, 1);
    sfSprite_setOrigin(c->menu.bg_2, origin);
    sfSprite_setOrigin(c->menu.bg_4, origin);
    origin.x = -50;
    origin.y = 0;
    sfSprite_setOrigin(c->menu.embers, origin);
}

void init_button_rect(core_t *c)
{
    c->menu.button_rect = malloc(sizeof(sfIntRect) * 3);
    c->menu.button_rect[0].width = 420;
    c->menu.button_rect[0].height = 105;
    c->menu.button_rect[1].width = 420;
    c->menu.button_rect[1].height = 105;
    c->menu.button_rect[2].width = 420;
    c->menu.button_rect[2].height = 105;
}

void init_menu(core_t *c) 
{
    init_menutxt(c);
    init_menutexture(c);
    init_menusprite(c);
    init_button_rect(c);
    c->menu.how_to_play_open = False;
    c->menu.fade_out_time = 0;
    c->menu.fade_out_curb = 0;
    c->menu.fade_in_time = 0;
    c->menu.fade_in_curb = 0;
}
