/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** creation.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_enemies(core_t *c, int nb)
{
    STAGE.e = NULL;
    for (int i = 0; i < nb; i++)
        add_node(c, &STAGE.e, 1, i);
}
