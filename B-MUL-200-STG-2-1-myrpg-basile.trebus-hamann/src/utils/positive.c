/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** positive.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

int positive(int nb)
{
    if (nb < 0)
        return 0;
    return nb;
}
