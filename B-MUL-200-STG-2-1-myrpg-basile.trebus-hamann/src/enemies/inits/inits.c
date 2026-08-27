/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** inits.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_textures_type1(sfTexture **texture_array)
{
    texture_array[0] = sfTexture_createFromFile(TYPE1_WALK, NULL);
    texture_array[1] = sfTexture_createFromFile(TYPE1_DEATH, NULL);
    texture_array[2] = sfTexture_createFromFile(TYPE1_IDLE, NULL);
    texture_array[3] = sfTexture_createFromFile(TYPE1_ATK1, NULL);
}

void init_text_type2(core_t *c)
{
    return;
}

void init_text_type3(core_t *c)
{
    return;
}

void init_enemies_textures(core_t *c)
{
    c->en_dic.textures = malloc(sizeof(sfTexture **) * 5);
    for (int i = 0; i < 5; i++)
        c->en_dic.textures[i] = malloc(sizeof(sfTexture *) * 10);
    c->en_dic.textures[4] = NULL;
    init_textures_type1(c->en_dic.textures[0]);
}
