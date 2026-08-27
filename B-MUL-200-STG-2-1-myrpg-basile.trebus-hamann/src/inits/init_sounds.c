/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_sounds.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void init_player_sounds(core_t *c)
{
    c->p.hurt_sound = malloc(sizeof(sfSound *) * 5);
    c->p.hurt_sound[0] = new_sound(c->p.hurt_sound[0],
    "sounds/p_hurt/hurt1.ogg");
    c->p.hurt_sound[1] = new_sound(c->p.hurt_sound[1],
    "sounds/p_hurt/hurt2.ogg");
    c->p.hurt_sound[2] = new_sound(c->p.hurt_sound[2],
    "sounds/p_hurt/hurt3.ogg");
    c->p.hurt_sound[3] = new_sound(c->p.hurt_sound[3],
    "sounds/p_hurt/hurt4.ogg");
    c->p.hurt_sound[4] = NULL;
}

static void init_enemies_sounds(core_t *c)
{
    c->audio.t1_hurt = new_sound(c->audio.t1_hurt, SOUND_TYPE1_HURT);
    c->audio.t1_death = malloc(sizeof(sfSound *) * 5);
    c->audio.t1_death[0] = new_sound(c->audio.t1_death[0], SOUND_TYPE1_DEATH1);
    c->audio.t1_death[1] = new_sound(c->audio.t1_death[1], SOUND_TYPE1_DEATH2);
    c->audio.t1_death[2] = new_sound(c->audio.t1_death[2], SOUND_TYPE1_DEATH3);
    c->audio.t1_death[3] = new_sound(c->audio.t1_death[3], SOUND_TYPE1_DEATH4);
    c->audio.t1_death[4] = NULL;
}

static void init_blacksmith_sounds(core_t *c)
{
    c->audio.anvil = malloc(sizeof(sfSound *) * 4);
    c->audio.anvil[0] = new_sound(c->audio.anvil[0], "sounds/anvil1.ogg");
    c->audio.anvil[1] = new_sound(c->audio.anvil[1], "sounds/anvil2.ogg");
    c->audio.anvil[2] = new_sound(c->audio.anvil[2], "sounds/anvil3.ogg");
    c->audio.anvil[3] = NULL;
}

static void init_sounds_2(core_t *c)
{
    c->audio.p_death = new_sound(c->audio.landing_sound,
    "sounds/you_died.ogg");
    c->audio.roll_sound = new_sound(c->audio.roll_sound,
    "sounds/roll_sound.ogg");
    c->audio.camp = new_sound(c->audio.camp,
    "sounds/campfire.ogg");
    c->audio.chest_open = new_sound(c->audio.chest_open,
    "sounds/chest_open.ogg");
    c->audio.pickup = new_sound(c->audio.pickup,
    "sounds/pickup_item.ogg");
    c->audio.ambient_music = sfMusic_createFromFile("sounds/ambient_music.ogg");
    c->audio.menu_music = sfMusic_createFromFile("sounds/menu_music.ogg");
    init_player_sounds(c);
    sfMusic_setLoop(c->audio.ambient_music, sfTrue);
    sfMusic_setLoop(c->audio.menu_music, sfTrue);
    sfMusic_play(c->audio.menu_music);
    init_enemies_sounds(c);
    init_blacksmith_sounds(c);
}

void init_sounds(core_t *c)
{
    c->audio.slash_sounds = malloc(sizeof(sfSound *) * 5);
    c->audio.slash_sounds[0] = new_sound(c->audio.slash_sounds[0],
    "sounds/pattack/slash1.ogg\0");
    c->audio.slash_sounds[1] = new_sound(c->audio.slash_sounds[0],
    "sounds/pattack/slash2.ogg\0");
    c->audio.slash_sounds[2] = new_sound(c->audio.slash_sounds[0],
    "sounds/pattack/slash3.ogg\0");
    c->audio.slash_sounds[3] = new_sound(c->audio.slash_sounds[0],
    "sounds/pattack/slash4.ogg\0");
    c->audio.slash_sounds[4] = NULL;
    c->audio.fall_atck_impact = new_sound(c->audio.fall_atck_impact,
    "sounds/pattack/fall_atk_impact.ogg\0");
    c->audio.roll_sound = new_sound(c->audio.roll_sound,
    "sounds/roll_sound.ogg");
    c->audio.landing_sound = new_sound(c->audio.landing_sound,
    "sounds/landing.ogg");
    init_sounds_2(c);
}
