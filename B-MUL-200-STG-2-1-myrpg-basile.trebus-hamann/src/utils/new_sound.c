/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** new_sound.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

sfSound *new_sound(sfSound *new_sound, const char *buffer_location)
{
    sfSoundBuffer *new_s = sfSoundBuffer_createFromFile(buffer_location);

    new_sound = sfSound_create();
    sfSound_setBuffer(new_sound, new_s);
    return (new_sound);
}
