/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_text.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_sftext(core_t *c, sfText **txt, int size)
{
    *txt = sfText_create();
    sfText_setCharacterSize(*txt, size);
    sfText_setFont(*txt,  c->menu.title_font);
    sfText_setOutlineColor(*txt, sfBlack);
    sfText_setOutlineThickness(*txt, 2);
    sfText_setString(*txt, NULL);
}
