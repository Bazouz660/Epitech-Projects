/*
** EPITECH PROJECT, 2022
** sfqsfsqf
** File description:
** fsqfsqfsqf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_bar(core_t *c)
{
    sfVector2f pos = {860, 685};

    c->option.bar_scale.x = 400;
    c->option.bar_scale.y = 25;
    c->option.bar = sfRectangleShape_create();
    sfRectangleShape_setTexture(c->option.bar, 
    sfTexture_createFromFile("sprites/rectangle.jpg", NULL), sfTrue);
    sfRectangleShape_setPosition(c->option.bar, pos);
}

void init_sound_bar(core_t *c)
{
    sfVector2f pos = {850, 650};

    c->option.sound_bar_s = sfSprite_create();
    c->option.sound_bar_t = sfTexture_createFromFile("sprites/button/phase1_button.png", NULL);
    sfSprite_setTexture(c->option.sound_bar_s, c->option.sound_bar_t, sfTrue);
    sfSprite_setPosition(c->option.sound_bar_s, pos);
}

void init_plus(core_t *c)
{
    sfVector2f pos = {1300, 650};

    c->option.up_rect.width = 70;
    c->option.up_rect.height = 79;
    c->option.up_s = sfSprite_create();
    c->option.up_t = sfTexture_createFromFile(BUTTON_UP_PATH, NULL);
    sfSprite_setTexture(c->option.up_s, c->option.up_t, sfTrue);
    sfSprite_setPosition(c->option.up_s, pos);
}

void init_less(core_t *c)
{
    sfVector2f pos = {750, 650};

    c->option.down_rect.width = 70;
    c->option.down_rect.height = 79;
    c->option.down_s = sfSprite_create();
    c->option.down_t = sfTexture_createFromFile(BUTTON_DOWN_PATH, NULL);
    sfSprite_setTexture(c->option.down_s, c->option.down_t, sfTrue);
    sfSprite_setPosition(c->option.down_s, pos);
}

void init_sound(core_t *c)
{
    c->audio.volume = 100;
    c->audio.button_click = new_sound(c->audio.button_click, 
    SOUND_EFFECT_PATH);
    init_bar(c);
    init_sound_bar(c);
    init_plus(c);
    init_less(c);
}