/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_frect.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

sfFloatRect init_frect(float left, float top, float width, float height)
{
    sfFloatRect rect = {left, top, width, height};

    return rect;
}

sfIntRect init_irect(int left, int top, int width, int height)
{
    sfIntRect rect = {left, top, width, height};

    return rect;
}

sfVector2f init_fvect(float x, float y)
{
    sfVector2f vector = {x, y};

    return vector;
}
